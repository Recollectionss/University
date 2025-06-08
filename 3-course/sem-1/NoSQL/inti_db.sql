
DROP TABLE IF EXISTS UserSessions;
DROP TABLE IF EXISTS UserTeams CASCADE ;
DROP TABLE IF EXISTS ProjectMilestones;
DROP TABLE IF EXISTS TaskLabels;
DROP TABLE IF EXISTS Teams CASCADE;
DROP TABLE IF EXISTS Comments;
DROP TABLE IF EXISTS Notifications CASCADE ;
DROP TABLE IF EXISTS Files;
DROP TABLE IF EXISTS Labels;
DROP TABLE IF EXISTS ActivityLog,Settings,Tasks,Projects,Roles;
DROP TABLE IF EXISTS Users CASCADE;

DROP VIEW IF EXISTS UserInfo,UserNotification;
DROP FUNCTION IF EXISTS get_user_full_info;


CREATE TABLE Users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP,
    last_modified_by INT REFERENCES Users(id)
);

CREATE TABLE Roles (
    id SERIAL PRIMARY KEY,
    role_name VARCHAR(50) UNIQUE NOT NULL
);

CREATE TABLE Projects (
    id SERIAL PRIMARY KEY,
    project_name VARCHAR(255) NOT NULL,
    description TEXT,
    owner_id INT REFERENCES Users(id),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP,
    last_modified_by INT REFERENCES Users(id)
);

CREATE TABLE Teams (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    project_id INT REFERENCES Projects(id),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP
);

ALTER TABLE Projects add team_id INT REFERENCES Teams(id);

CREATE TABLE Tasks (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    project_id INT REFERENCES Projects(id),
    assigned_to INT REFERENCES Users(id),
    status VARCHAR(50),
    priority VARCHAR(50),
    due_date DATE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP,
    last_modified_by INT REFERENCES Users(id)
);

CREATE TABLE Comments (
    id SERIAL PRIMARY KEY,
    task_id INT REFERENCES Tasks(id),
    user_id INT REFERENCES Users(id),
    content TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP
);

CREATE TABLE Files (
    id SERIAL PRIMARY KEY,
    task_id INT REFERENCES Tasks(id),
    file_path VARCHAR(255) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP
);

CREATE TABLE UserTeams (
    user_id INT REFERENCES Users(id),
    team_id INT REFERENCES Teams(id),
    role_id INT REFERENCES Roles(id),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE ProjectMilestones (
    id SERIAL PRIMARY KEY,
    project_id INT REFERENCES Projects(id),
    name VARCHAR(255) NOT NULL,
    description TEXT,
    due_date DATE,
    status VARCHAR(50),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP
);

CREATE TABLE Notifications (
    id SERIAL PRIMARY KEY,
    user_id INT REFERENCES Users(id),
    message TEXT NOT NULL,
    is_read BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Labels (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    color VARCHAR(20),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE TaskLabels (
    task_id INT REFERENCES Tasks(id),
    label_id INT REFERENCES Labels(id)
);

CREATE TABLE ActivityLog (
    id SERIAL PRIMARY KEY,
    user_id INT REFERENCES Users(id),
    entity_type VARCHAR(50),
    entity_id INT,
    action VARCHAR(255),
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Settings (
    id SERIAL PRIMARY KEY,
    user_id INT REFERENCES Users(id),
    setting_key VARCHAR(100),
    setting_value TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE UserSessions (
    id SERIAL PRIMARY KEY,
    user_id INT REFERENCES Users(id),
    session_token VARCHAR(255),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    expires_at TIMESTAMP
);

CREATE OR REPLACE FUNCTION update_timestamp()
RETURNS TRIGGER AS $$
BEGIN
   NEW.updated_at = NOW();
   RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER update_users_timestamp
BEFORE UPDATE ON Users
FOR EACH ROW
EXECUTE FUNCTION update_timestamp();

CREATE TRIGGER update_projects_timestamp
BEFORE UPDATE ON Projects
FOR EACH ROW
EXECUTE FUNCTION update_timestamp();

CREATE TRIGGER update_tasks_timestamp
BEFORE UPDATE ON Tasks
FOR EACH ROW
EXECUTE FUNCTION update_timestamp();

CREATE TRIGGER update_comments_timestamp
BEFORE UPDATE ON Comments
FOR EACH ROW
EXECUTE FUNCTION update_timestamp();


CREATE OR REPLACE FUNCTION log_user_activity()
RETURNS TRIGGER AS $$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.id, 'User', NEW.id, 'INSERT', NOW());
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.id, 'User', NEW.id, 'UPDATE', NOW());
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (OLD.id, 'User', OLD.id, 'DELETE', NOW());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER user_activity_trigger
AFTER INSERT OR UPDATE OR DELETE ON Users
FOR EACH ROW EXECUTE FUNCTION log_user_activity();
CREATE OR REPLACE FUNCTION log_project_activity()
RETURNS TRIGGER AS $$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.owner_id, 'Project', NEW.id, 'INSERT', NOW());
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.owner_id, 'Project', NEW.id, 'UPDATE', NOW());
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (OLD.owner_id, 'Project', OLD.id, 'DELETE', NOW());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER project_activity_trigger
AFTER INSERT OR UPDATE OR DELETE ON Projects
FOR EACH ROW EXECUTE FUNCTION log_project_activity();
CREATE OR REPLACE FUNCTION log_task_activity()
RETURNS TRIGGER AS $$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.assigned_to, 'Task', NEW.id, 'INSERT', NOW());
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.assigned_to, 'Task', NEW.id, 'UPDATE', NOW());
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (OLD.assigned_to, 'Task', OLD.id, 'DELETE', NOW());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER task_activity_trigger
AFTER INSERT OR UPDATE OR DELETE ON Tasks
FOR EACH ROW EXECUTE FUNCTION log_task_activity();

CREATE VIEW UserInfo AS
SELECT
    u.id,
    u.username,
    u.email,
    t.name,
    r.role_name,
    p.project_name
FROM Users u
JOIN UserTeams ut ON u.id = ut.user_id
JOIN Teams t ON ut.team_id = t.id
JOIN Roles r on ut.role_id = r.id
JOIN Projects p on t.project_id = p.id;

CREATE VIEW UserNotification AS
SELECT
    u.id,
    u.username,
    n.message
FROM Users u
JOIN notifications n on u.id = n.user_id;

CREATE VIEW ProjectInfo AS
SELECT
    p.id AS project_id,
    p.project_name,
    p.description,
    p.owner_id,
    T.id AS team_id,
    T.name,T
FROM Projects p
JOIN Teams T on p.id = T.project_id;


CREATE OR REPLACE FUNCTION send_task_notification(p_user_id INT, p_task_id INT, p_message TEXT)
RETURNS VOID AS $$
BEGIN
    INSERT INTO Notifications (user_id, message, created_at)
    VALUES (p_user_id, p_message, NOW());
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER task_status_update_notification
AFTER UPDATE OF status ON Tasks
FOR EACH ROW
WHEN (OLD.status IS DISTINCT FROM NEW.status)
EXECUTE FUNCTION send_task_notification(NEW.assigned_to, NEW.id, 'Task status updated to ' || NEW.status);


CREATE OR REPLACE FUNCTION get_user_full_info(p_user_id INT)
RETURNS TABLE (
    user_id INT,
    username VARCHAR,
    email VARCHAR,
    created_at TIMESTAMP,
    notification_message TEXT,
    notification_is_read BOOLEAN,
    setting_key VARCHAR,
    setting_value TEXT,
    project_id INT,
    project_name VARCHAR,
    project_description TEXT,
    project_created_at TIMESTAMP
) AS $$
BEGIN
    RETURN QUERY
    SELECT
        u.id AS user_id,
        u.username,
        u.email,
        u.created_at,
        n.message AS notification_message,
        n.is_read AS notification_is_read,
        s.setting_key,
        s.setting_value,
        p.id AS project_id,
        p.project_name,
        p.description AS project_description,
        p.created_at AS project_created_at
    FROM Users u
    LEFT JOIN Notifications n ON u.id = n.user_id
    LEFT JOIN Settings s ON u.id = s.user_id
    LEFT JOIN Projects p ON u.id = p.owner_id
    WHERE u.id = p_user_id;
END;
$$ LANGUAGE plpgsql;


   CREATE OR REPLACE FUNCTION log_user_activity()
RETURNS TRIGGER AS $$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.id, 'User', NEW.id, 'INSERT', NOW());
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.id, 'User', NEW.id, 'UPDATE', NOW());
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (OLD.id, 'User', OLD.id, 'DELETE', NOW());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER user_activity_trigger
AFTER INSERT OR UPDATE OR DELETE ON Users
FOR EACH ROW EXECUTE FUNCTION log_user_activity();
CREATE OR REPLACE FUNCTION log_project_activity()
RETURNS TRIGGER AS $$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.owner_id, 'Project', NEW.id, 'INSERT', NOW());
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.owner_id, 'Project', NEW.id, 'UPDATE', NOW());
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (OLD.owner_id, 'Project', OLD.id, 'DELETE', NOW());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER project_activity_trigger
AFTER INSERT OR UPDATE OR DELETE ON Projects
FOR EACH ROW EXECUTE FUNCTION log_project_activity();
CREATE OR REPLACE FUNCTION log_task_activity()
RETURNS TRIGGER AS $$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.assigned_to, 'Task', NEW.id, 'INSERT', NOW());
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (NEW.assigned_to, 'Task', NEW.id, 'UPDATE', NOW());
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO ActivityLog (user_id, entity_type, entity_id, action, timestamp)
        VALUES (OLD.assigned_to, 'Task', OLD.id, 'DELETE', NOW());
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER task_activity_trigger
AFTER INSERT OR UPDATE OR DELETE ON Tasks
FOR EACH ROW EXECUTE FUNCTION log_task_activity();


INSERT INTO Users (username, email, password, created_at, updated_at, last_modified_by)
VALUES
('john_doe', 'john@example.com', 'hashed_password1', NOW(), NOW(), 1),
('jane_smith', 'jane@example.com', 'hashed_password2', NOW(), NOW(), 1),
('admin_user', 'admin@example.com', 'hashed_password3', NOW(), NOW(), 1);
INSERT INTO Roles (role_name)
VALUES
('SEO');
INSERT INTO Projects (name, description, owner_id, created_at, updated_at, last_modified_by)
VALUES
('Project Alpha', 'A high-priority project', 1, NOW(), NOW(), 1),
('Project Beta', 'A side project for experimentation', 2, NOW(), NOW(), 2);
INSERT INTO Tasks (name, description, project_id, assigned_to, status, priority, due_date, created_at, updated_at, last_modified_by)
VALUES
('Task 1', 'Complete initial setup', 1, 1, 'in_progress', 'high', '2024-12-01', NOW(), NOW(), 1),
('Task 2', 'Design UI mockups', 1, 2, 'pending', 'medium', '2024-12-10', NOW(), NOW(), 1),
('Task 3', 'Implement authentication', 2, 2, 'in_progress', 'high', '2024-12-15', NOW(), NOW(), 2);
INSERT INTO Comments (task_id, user_id, content, created_at, updated_at)
VALUES
(1, 1, 'Started working on the task.', NOW(), NOW()),
(1, 2, 'Please review the setup.', NOW(), NOW()),
(3, 2, 'Authentication is half done.', NOW(), NOW());
INSERT INTO Files (task_id, file_path, created_at, updated_at)
VALUES
(1, '/files/setup_guide.pdf', NOW(), NOW()),
(3, '/files/authentication_spec.docx', NOW(), NOW());
INSERT INTO Teams (name, description, created_at, updated_at)
VALUES
('Alpha Team', 'Core team working on Project Alpha', NOW(), NOW()),
('Beta Team', 'Experimental team working on side projects', NOW(), NOW());
INSERT INTO UserTeams (user_id, team_id, created_at, updated_at)
VALUES
(1, 1, NOW(), NOW()),  -- John Doe у Alpha Team
(2, 2, NOW(), NOW());  -- Jane Smith у Beta Team
INSERT INTO ProjectMilestones (project_id, name, description, due_date, status, created_at, updated_at)
VALUES
(1, 'Milestone 1', 'Complete the initial setup and documentation.', '2024-12-05', 'in_progress', NOW(), NOW()),
(2, 'Milestone 2', 'Finalize UI design and review.', '2024-12-15', 'pending', NOW(), NOW());
INSERT INTO Notifications (user_id, message, is_read, created_at, updated_at)
VALUES
(1, 'You have been assigned a new task: Task 1.', FALSE, NOW(), NOW()),
(2, 'You have a new comment on Task 1.', TRUE, NOW(), NOW());
INSERT INTO Labels (name, color, created_at, updated_at)
VALUES
('Urgent', '#ff0000', NOW(), NOW()),
('UI/UX', '#00ff00', NOW(), NOW()),
('Backend', '#0000ff', NOW(), NOW());
INSERT INTO TaskLabels (task_id, label_id)
VALUES
(1, 1),  -- Task 1 має мітку Urgent
(2, 2),  -- Task 2 має мітку UI/UX
(3, 3);  -- Task 3 має мітку Backend
INSERT INTO Settings (user_id, setting_key, setting_value, created_at, updated_at)
VALUES
(1, 'theme', 'dark', NOW(), NOW()),
(2, 'notifications', 'enabled', NOW(), NOW());
INSERT INTO UserSessions (user_id, session_token, created_at, expires_at)
VALUES
(1, 'token_123456', NOW(), NOW() + INTERVAL '1 hour'),
(2, 'token_654321', NOW(), NOW() + INTERVAL '1 hour');
