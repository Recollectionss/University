package gift.DAO;

import gift.interfaces.GiftDAOInterface;
import gift.model.Gift;

import java.sql.*;

public class GiftDAO implements GiftDAOInterface {
    final static String _createQuery ="INSERT INTO Gift(name, total_cost) VALUES (?,?)";
    final static String _deleteQuery = "DELETE FROM Gift WHERE id = ?";
    final static String _updateQuery = "UPDATE Gift SET name = ?, total_cost = ? WHERE id = ?";
    final static String _selectQuery = "SELECT * FROM Gift WHERE id = ?";
    final static String _checkTableExistQuery = "SELECT id FROM Gift";
    final static String _selectMaxIdQuery = "SELECT id FROM Gift ORDER BY id DESC LIMIT 1";
    final static String _createTableQuery =
            "CREATE TABLE IF NOT EXISTS Gift(" +
            "id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT," +
            "name TEXT," +
            "total_cost INTEGER" +
            ");";

    Connection _connection = null;

    public GiftDAO() {

    }

    @Override
    public void create(Gift gift) throws SQLException {
        try (PreparedStatement statement = _connection.prepareStatement(_createQuery)) {
            statement.setString(1, gift.getName());
            statement.setInt(2,gift.getTotalCost());

            statement.executeUpdate();
        }
    }

    @Override
    public void delete(int id) throws SQLException {
        try (PreparedStatement statement = _connection.prepareStatement(_deleteQuery)) {
            statement.setInt(1, id);

            statement.executeUpdate();
        }
    }

    @Override
    public void update(Gift gift) throws SQLException {
        try (PreparedStatement statement = _connection.prepareStatement(_updateQuery)) {
            statement.setString(1, gift.getName());
            statement.setInt(2, gift.getTotalCost());
            statement.setInt(3, gift.getId());

            statement.executeUpdate();
        }
    }

    @Override
    public Gift select(int id) throws SQLException {
        try(PreparedStatement statement = _connection.prepareStatement(_selectQuery)) {
            statement.setInt(1, id);
            ResultSet result = statement.executeQuery();

            return new Gift(result.getInt("id"),result.getString("name"));
        }
    }

    @Override
    public int selectWithMaxId() throws SQLException {
        try(PreparedStatement statement = _connection.prepareStatement(_selectMaxIdQuery)) {
            ResultSet result = statement.executeQuery();
            return result.getInt("id");
        }
    }

    @Override
    public boolean checkTable() throws SQLException {
        try(PreparedStatement statement = _connection.prepareStatement(_checkTableExistQuery)) {
            statement.executeQuery();
            return true;
        } catch (SQLException e) {
            System.out.println("Table not exists" + e.getMessage());
            return false;
        }
    }

    @Override
    public void createTable() throws SQLException {
        try(Statement statement = _connection.createStatement()) {
            statement.execute(_createTableQuery);
        }
    }

    public GiftDAO setConnection(Connection connection){
        if(connection == null) {
            throw new NullPointerException("connection is null");
        }
        this._connection = connection;

        try {
            if (!checkTable()){
                createTable();
                System.out.println("Table created");
            }
            return this;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public String getCreateQuery() {return _createQuery;}
    public String getUpdateQuery() {return _updateQuery;}
    public String getDeleteQuery() {return _deleteQuery;}
    public String getSelectQuery() {return _selectQuery;}
}
