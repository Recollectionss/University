package gift.interfaces;

import gift.model.Gift;

import java.sql.SQLException;

public interface GiftDAOInterface {
    void create(Gift gift)throws SQLException;
    void delete(int id)throws SQLException;
    void update(Gift gift)throws SQLException;
    Gift select(int id)throws SQLException;
    int selectWithMaxId()throws SQLException;

    boolean checkTable() throws SQLException;
    void createTable() throws SQLException;
}
