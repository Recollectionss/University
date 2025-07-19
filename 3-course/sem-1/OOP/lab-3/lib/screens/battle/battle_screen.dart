import 'package:flutter/material.dart';
import 'package:lab/models/cell/cell.dart';
import 'package:lab/computer_player/computer_player.dart';
import 'package:lab/computer_player/strategy/game_strategy.dart';
import 'package:lab/models/ship/ship.dart';

class BattleScreen extends StatefulWidget {
  final List<List<Cell>> playerMatrix;
  final GameStrategy computerStrategy;

  const BattleScreen({
    required this.playerMatrix,
    required this.computerStrategy,
    super.key,
  });

  @override
  _BattleScreenState createState() => _BattleScreenState();
}

class _BattleScreenState extends State<BattleScreen> {
  late List<List<Cell>> playerMatrix;
  late ComputerPlayer computerPlayer;
  bool isPlayerTurn = true;

  @override
  void initState() {
    super.initState();
    playerMatrix = widget.playerMatrix;
    computerPlayer = ComputerPlayer(
      strategy: widget.computerStrategy,
      userMatrix: playerMatrix,
    );
  }

  void handleShot(int row, int col) {
    if (isPlayerTurn && _makeShot(computerPlayer.matrix, row, col)) {
      setState(() => isPlayerTurn = false);
      Future.delayed(const Duration(seconds: 1), computerTurn);
    }
  }

  bool _makeShot(List<List<Cell>> matrix, int row, int col) {
    final cell = matrix[row][col];
    if (cell.isShot) return false;

    setState(() {
      cell.isShot = true;
      cell.color = cell.isOccupied ? Colors.red : Colors.grey;
      if (cell.isOccupied && isPlayerTurn) {
        print("PREV");
        print(Offset(col.toDouble(), row.toDouble()));
        widget.computerStrategy.onHit(Offset(col.toDouble(), row.toDouble()));
      }
      if (_isShipDestroyedAroundShot(matrix, row, col) && isPlayerTurn) {
        widget.computerStrategy.onKill();
        print("Кill.");
      }
    });
    return !cell.isOccupied;
  }


  void computerTurn() {
    final move = computerPlayer.makeMove();
    if (_makeShot(playerMatrix, move.x, move.y)) {
      setState(() => isPlayerTurn = true);
    } else {
      Future.delayed(const Duration(seconds: 1), computerTurn);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(isPlayerTurn ? "Your turn" : "Computer turn"),
        backgroundColor: const Color.fromARGB(255, 9, 41, 104),
      ),
      backgroundColor: Colors.white,
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          const Text("You field"),
          _buildMatrix(playerMatrix, false),
          const SizedBox(height: 20),
          const Text("Computer Field"),
          _buildMatrix(computerPlayer.matrix, true),
        ],
      ),
    );
  }

  Widget _buildMatrix(List<List<Cell>> matrix, bool isClickable) {
    const double cellSize = 30.0;
    return Center(
      child: Container(
        width: cellSize * matrix.length,
        height: cellSize * matrix.length,
        decoration: BoxDecoration(
          border: Border.all(color: Colors.black, width: 2.0),
        ),
        child: Stack(
          children: List.generate(matrix.length, (row) {
            return List.generate(matrix.length, (col) {
              return Positioned(
                left: col * cellSize,
                top: row * cellSize,
                child: GestureDetector(
                  onTap: isClickable && isPlayerTurn ? () => handleShot(row, col) : null,
                  child: Container(
                    width: cellSize,
                    height: cellSize,
                    decoration: BoxDecoration(
                      border: Border.all(color: Colors.black),
                      color: _getCellColor(matrix[row][col], !isClickable),
                    ),
                  ),
                ),
              );
            });
          }).expand((i) => i).toList(),
        ),
      ),
    );
  }

  Color _getCellColor(Cell cell, bool isPlayerMatrix) {
    if (cell.isShot) {
      return cell.isOccupied ? Colors.red : Colors.grey;
    } else if (cell.isOccupied && isPlayerMatrix) {
      return Colors.blue.withOpacity(0.5);
    }
    return Colors.transparent;
  }

  bool _isShipDestroyedAroundShot(List<List<Cell>> matrix, int shotRow, int shotCol) {
    final cell = matrix[shotRow][shotCol];
    if (cell.ship == null) return false;

    final ship = cell.ship!;
    final shipCells = _getShipCellsAround(matrix, shotRow, shotCol, ship);

    if (shipCells.every((c) => c.isShot)) {
      print("All cells in this ship destroyed");
      _markSurroundingCells(matrix, shotRow, shotCol, shipCells);
      return true;
    }
    return false;
  }

  List<Cell> _getShipCellsAround(List<List<Cell>> matrix, int shotRow, int shotCol, Ship ship) {
    List<Cell> shipCells = [];
    print(ship.isHorizontal);

    if (ship.isHorizontal) {
      for (int i = 0; i <= ship.size; i++) {
        if (shotCol + i < 10) {
          final cell = matrix[shotRow][shotCol + i];
          if (cell.ship == ship) {
            shipCells.add(cell);
          }
        }
        if (shotCol - i >= 0) {
          final cell = matrix[shotRow][shotCol - i];
          if (cell.ship == ship) {
            shipCells.add(cell);
          }
        }
      }
    } else {
      for (int i = 0; i < ship.size; i++) {
        if (shotRow + i < matrix.length) {
          final cell = matrix[shotRow + i][shotCol];
          if (cell.ship == ship) {
            shipCells.add(cell);
          }
        }
        if (shotRow - i >= 0) {
          final cell = matrix[shotRow - i][shotCol];
          if (cell.ship == ship) {
            shipCells.add(cell);
          }
        }
      }
    }

    return shipCells;
  }

  void _markSurroundingCells(List<List<Cell>> matrix, int shotRow, int shotCol, List<Cell> shipCells) {
    Set<Cell> surroundingCells = {};

    for (var shipCell in shipCells) {
      for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
          final row = shipCell.row + dr;
          final col = shipCell.col + dc;

          if (_isInBounds(row, col)) {
            final surroundingCell = matrix[row][col];
            if (!shipCells.contains(surroundingCell) && !surroundingCell.isShot) {
              surroundingCells.add(surroundingCell);
            }
          }
        }
      }
    }

    for (var surroundingCell in surroundingCells) {
      setState(() {
        surroundingCell.isShot = true;
        surroundingCell.color = Colors.grey;
      });
    }
  }

  bool _isInBounds(int row, int col) => row >= 0 && row < 10 && col >= 0 && col < 10;

}