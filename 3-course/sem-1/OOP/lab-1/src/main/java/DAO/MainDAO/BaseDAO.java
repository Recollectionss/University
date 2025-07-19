package DAO.MainDAO;

import DAO.interfaces.MainDAOInterface;
import candy.DAO.CandyDAO;
import candy.model.Candy;
import gift.DAO.GiftDAO;
import gift.model.Gift;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;

public class BaseDAO implements MainDAOInterface {
    Connection _connection;
    GiftDAO _giftDAO;
    CandyDAO _candyDAO;

    String DbUrl = "jdbc:sqlite:identifier.sqlite";

    public BaseDAO(){
        _giftDAO = new GiftDAO();
        _candyDAO = new CandyDAO();
    }

    public BaseDAO openConnection(){
        try {
             _connection = DriverManager.getConnection(DbUrl);
            _giftDAO.setConnection(_connection);
            _candyDAO.setConnection(_connection);
            return this;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
    public void closeConnection(){
        try {
            _connection.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }


    public BaseDAO saveGiftWithCandy(Gift gift) throws SQLException {
        _connection.setAutoCommit(false);
        try {

            _giftDAO.setConnection(_connection).create(gift);

            ArrayList<Candy> candies = gift.get_candies();
            for (Candy candy : candies) {
                _candyDAO.setConnection(_connection).create(candy);
            }

            _connection.commit();
        } catch (SQLException e) {
            _connection.rollback();
            throw new RuntimeException(e);
        }finally {
            _connection.setAutoCommit(true);
        }
        return this;
    }

    public Gift getGiftWithCandy(int id) throws SQLException {
        _connection.setAutoCommit(false);
        try {
            Gift gift =_giftDAO.setConnection(_connection).select(id);

            gift.setCandies(_candyDAO.setConnection(_connection).selectAllFromCurrentGift(id));

            _connection.commit();

            return gift;
        }catch (SQLException e) {
            _connection.rollback();
            throw new RuntimeException(e);
        }finally {
            _connection.setAutoCommit(true);
        }
    }
    public BaseDAO deleteGiftWithCandy(int id) throws SQLException {
        _connection.setAutoCommit(false);
        try{
            _giftDAO.setConnection(_connection).delete(id);

            _candyDAO.setConnection(_connection).deleteWithGift(id);
        }catch (SQLException e){
            _connection.rollback();
            throw new RuntimeException(e);
        }finally {
            _connection.setAutoCommit(true);
        }
        return this;
    }

    public CandyDAO getCandyDAO() {return _candyDAO;}
    public GiftDAO getGiftDAO() {return _giftDAO;}
}
