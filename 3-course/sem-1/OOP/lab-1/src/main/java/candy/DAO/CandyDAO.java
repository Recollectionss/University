package candy.DAO;

import candy.enums.CandyType;
import candy.interfaces.CandyDAOInterface;
import candy.model.Candy;

import java.sql.*;
import java.util.ArrayList;

public class CandyDAO implements CandyDAOInterface {

    final static String _createQuery ="INSERT INTO Candy(name, type, price, weight, sugar, gift_id) VALUES (?,?,?,?,?,?)";
    final static String _deleteQuery = "DELETE FROM Candy WHERE id = ?";
    final static String DELETE_WHERE_GIFT_ID = "DELETE FROM CANDY WHERE gift_id = ?";
    final static String _updateQuery = "UPDATE Candy SET name = ?, type = ?, price = ?, weight = ?, sugar = ?, gift_id = ? WHERE id = ?";
    final static String _selectQuery = "SELECT * FROM Candy WHERE id = ?";
    final static String _selectAllFromGiftQuery = "SELECT * FROM Candy WHERE gift_id = ?";
    final static String _checkTableExistQuery = "SELECT id FROM Candy";
    final static String _selectMaxIdQuery = "SELECT id FROM Candy ORDER BY id DESC LIMIT 1";
    final static String _createTableQuery =
            "CREATE TABLE IF NOT EXISTS Candy(" +
            "id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT," +
            "name TEXT," +
            "type TEXT," +
            "price INTEGER," +
            "weight INTEGER," +
            "sugar INTEGER," +
            "gift_id INTEGER," +
            "FOREIGN KEY(gift_id) REFERENCES Gift(id)" +
            ");";

    Connection _connection;


    public CandyDAO() {}

    @Override
    public void create(Candy candy) throws SQLException {
        try(PreparedStatement statement = prepareStatement(_createQuery,candy)) {

            statement.execute();
        }
    }

    @Override
    public void delete(int id) throws SQLException {
        try(PreparedStatement statement = _connection.prepareStatement(_deleteQuery)) {
            statement.setInt(1,id);

            statement.execute();
        }
    }
    public void deleteWithGift(int gift_id) throws SQLException {
        try(PreparedStatement statement = _connection.prepareStatement(DELETE_WHERE_GIFT_ID)){
            statement.setInt(1,gift_id);
            statement.execute();
        }
    }

    @Override
    public void update(Candy candy) throws SQLException {
        try(java.sql.PreparedStatement statement = prepareStatement(_updateQuery,candy)) {
            statement.setInt(7, candy.getId());

            statement.execute();
        }
    }

    @Override
    public Candy select(int id) throws SQLException {
        try (PreparedStatement statement = _connection.prepareStatement(_selectQuery)) {
            statement.setInt(1, id);
            try (ResultSet rs = statement.executeQuery()) {
                if (rs.next()) {
                    return new Candy.CandyBuilder()
                            .withId(rs.getInt("id"))
                            .withName(rs.getString("name"))
                            .withCandyType(CandyType.valueOf(rs.getString("type")))
                            .withSugar(rs.getInt("sugar"))
                            .withPrice(rs.getInt("price"))
                            .withWeight(rs.getInt("weight"))
                            .withGiftId(rs.getInt("gift_id"))
                            .build();
                }
            }
        }
        return null;
    }

    @Override
    public ArrayList<Candy> selectAllFromCurrentGift(int giftId) throws SQLException {
        try(PreparedStatement statement = _connection.prepareStatement(_selectAllFromGiftQuery)) {
            statement.setInt(1,giftId);

            ArrayList<Candy> candies = new ArrayList<>();
            ResultSet rs = statement.executeQuery();

            while (rs.next()) {
                candies.add(
                        new Candy.CandyBuilder()
                                .withId(rs.getInt("id"))
                                .withName(rs.getString("name"))
                                .withCandyType(CandyType.valueOf(rs.getString("type")))
                                .withSugar(rs.getInt("sugar"))
                                .withPrice(rs.getInt("price"))
                                .withWeight(rs.getInt("weight"))
                                .withGiftId(rs.getInt("gift_Id"))
                                .build()
                );
            }
            return candies;
        }
    }

    @Override
    public boolean checkTable() {
        try (Statement statement = _connection.createStatement()){
            statement.execute(_checkTableExistQuery);
            return true;
        } catch (SQLException e) {
            System.out.println("Table not exists" + e.getMessage());
            return false;
        }
    }

    @Override
    public void createTable() throws SQLException {
        try (Statement statement = _connection.createStatement()){
            statement.execute(_createTableQuery);
        }
    }

    @Override
    public int selectWithMaxId()throws SQLException{
        try(PreparedStatement statement = _connection.prepareStatement(_selectMaxIdQuery)) {
            try (ResultSet resultSet = statement.executeQuery()) {
                if (resultSet.next()) {
                    return resultSet.getInt("id");
                }
            }
        }
        return -1;
    }

    public PreparedStatement prepareStatement(String sql, Candy candy) throws SQLException {
        PreparedStatement statement = _connection.prepareStatement(sql);

        statement.setString(1, candy.getName());
        statement.setString(2, String.valueOf(candy.getCandyType()));
        statement.setInt(3, candy.getPrice());
        statement.setInt(4, candy.getWeight());
        statement.setInt(5, candy.getSugar());
        statement.setInt(6,candy.getGiftId());

        return statement;
    }

    public CandyDAO setConnection(Connection connection) {
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
    public String getSelectAllQuery() {return _selectAllFromGiftQuery;}
}
