
import 'package:flutter/material.dart';
import 'package:lab/computer_player/strategy/easy_strategy.dart';
import 'package:lab/computer_player/strategy/game_strategy.dart';
import 'package:lab/computer_player/strategy/middle_strategy.dart';
import 'package:lab/models/cell/cell.dart';
import 'package:lab/components/matrix/matrix_paiter.dart';
import 'package:lab/models/ship/ship.dart';
import 'package:lab/utils/ship_placer.dart';

import '../battle/battle.dart';

class BattlePreparationScreen extends StatefulWidget {
  const BattlePreparationScreen({super.key});

  @override
  State<BattlePreparationScreen> createState() => _BattlePreparationScreenState();
}

class _BattlePreparationScreenState extends State<BattlePreparationScreen> {
  final List<List<Cell>> matrix = List.generate(
    10,
        (row) => List.generate(
      10,
          (col) => Cell(row: row, col: col, isOccupied: false, ship: null),
    ),
  );


  final List<Ship> ships = [
    Ship(size: 4, count: 1),
    Ship(size: 3, count: 2),
    Ship(size: 2, count: 3),
    Ship(size: 1, count: 4),
  ];

  Ship? currentShip;

  bool isHorizontal = true;
  late final ShipPlacer shipPlacer;

  List<List<Cell>> playerMatrix = List.generate(10, (row) => List.generate(10, (col) => Cell(row: row, col: col,isOccupied: false, ship: null)));

  GameStrategy? selectedDifficulty;

  bool get areAllShipsPlaced =>
      ships.every((ship) => ship.count == 0);

  bool get canContinue =>
      selectedDifficulty != null && areAllShipsPlaced;

  void selectDifficulty(GameStrategy difficulty) {
    setState(() {
      selectedDifficulty = difficulty;
    });
  }
  @override
  void initState() {
    super.initState();
    currentShip = ships.firstWhere((ship) => ship.count > 0, orElse: () => Ship(size: 0, count: 0));
    shipPlacer = ShipPlacer(matrix);

    placeShipsForPlayer();
  }


  void placeShipsForPlayer() {
    for (int i = 0; i < playerMatrix.length; i++) {
      for (int j = 0; j < playerMatrix[i].length; j++) {
        playerMatrix[i][j] = matrix[i][j];
      }
    }
  }

  bool placeShip(int startX, int startY) {
    if (currentShip == null) return false;

    if (shipPlacer.placeShip(startX, startY, currentShip!, isHorizontal)) {
      setState(() {
        currentShip!.count--;
        if (currentShip!.count == 0) {
          currentShip = ships.firstWhere((ship) => ship.count > 0, orElse: () => Ship(size: 0, count: 0));
        }
      });
      return true;
    }

    return false;
  }


  bool isPlacementValid(int startX, int startY, int shipSize, bool horizontal) {
    // Check if the ship fits within the grid
    if (horizontal) {
      if (startY + shipSize > 10) return false;
    } else {
      if (startX + shipSize > 10) return false;
    }

    for (int i = -1; i <= shipSize; i++) {
      for (int j = -1; j <= 1; j++) {
        int x = horizontal ? startX + j : startX + i;
        int y = horizontal ? startY + i : startY + j;

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
          if (matrix[x][y].isOccupied) {
            return false;
          }
        }
      }
    }
    return true;
  }

  void toggleOrientation() {
    setState(() {
      isHorizontal = !isHorizontal;
    });
  }

  void resetShips() {
    setState(() {
      for (var row in matrix) {
        for (var cell in row) {
          cell.isOccupied = false;
          cell.ship = null;
        }
      }
      ships.clear();
      ships.addAll([
        Ship(size: 4, count: 1),
        Ship(size: 3, count: 2),
        Ship(size: 2, count: 3),
        Ship(size: 1, count: 4),
      ]);
      currentShip = ships.firstWhere((ship) => ship.count > 0, orElse: () => Ship(size: 0, count: 0));
    });
  }



  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: const Color.fromARGB(255, 9, 41, 104),
      ),
      backgroundColor: Colors.white,
      body: Center(
        child: Column(
          children: [
            const SizedBox(height: 80),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Expanded(
                  child: ElevatedButton(
                    onPressed: toggleOrientation,
                    child: Text(isHorizontal
                        ? "Rotate to vertical"
                        : "Rotate to horizontal"),
                  ),
                ),
                const SizedBox(width: 20),
                Expanded(
                  child: Text(
                    'Current ship: ${currentShip?.size ?? 0}x, left: ${currentShip?.count ?? 0}',
                    style: const TextStyle(fontSize: 18),
                    textAlign: TextAlign.center,
                  ),
                ),
              ],
            ),
            const SizedBox(height: 20),
            SizedBox(
              width: 350, // 10 cells * 35px each
              height: 350, // 10 cells * 35px each
              child: Stack(
                children: [
                  CustomPaint(
                    size: const Size(350, 350),
                    painter: MatrixPainter(),
                  ),
                  ...List.generate(10, (rowIndex) {
                    return List.generate(10, (colIndex) {
                      return Positioned(
                        left: colIndex * 35.0,
                        top: rowIndex * 35.0,
                        child: GestureDetector(
                          onTap: () {
                            placeShip(rowIndex, colIndex);
                          },
                          child: Container(
                            width: 35.0,
                            height: 35.0,
                            decoration: BoxDecoration(
                              border: Border.all(color: Colors.black),
                              color: matrix[rowIndex][colIndex].isOccupied
                                  ? Colors.blue.withOpacity(0.5)
                                  : Colors.transparent,
                            ),
                          ),
                        ),
                      );
                    });
                  }).expand((element) => element).toList(),
                ],
              ),
            ),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: resetShips,
              style: ElevatedButton.styleFrom(backgroundColor: Colors.red),
              child: const Text("Reset Ships"),
            ),
            const SizedBox(height: 20),
            Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Column(
                  children: [
                    const Text("Difficulty:"),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        ElevatedButton(
                          child: const Text("Easy"),
                          onPressed: () => selectDifficulty(EasyStrategy()),
                          style: ElevatedButton.styleFrom(
                            backgroundColor: selectedDifficulty is EasyStrategy
                                ? Colors.green
                                : null,
                          ),
                        ),
                        const SizedBox(width: 30,),
                        ElevatedButton(
                          child: const Text("Middle"),
                          onPressed: () => selectDifficulty(MiddleStrategy()),
                          style: ElevatedButton.styleFrom(
                            backgroundColor: selectedDifficulty is MiddleStrategy
                                ? Colors.green
                                : null,
                          ),
                        ),
                        // ElevatedButton(
                        //   child: const Text("Hard"),
                        //   onPressed: () => selectDifficulty(HardStrategy()),
                        //   style: ElevatedButton.styleFrom(
                        //     backgroundColor: selectedDifficulty is HardStrategy
                        //         ? Colors.green
                        //         : null,
                        //   ),
                        // ),
                      ],
                    ),
                  ],
                ),
                const SizedBox(height: 30),
                ElevatedButton(
                  onPressed: canContinue
                      ? () {
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) =>
                            BattleScreen(playerMatrix: playerMatrix, computerStrategy: selectedDifficulty!),
                      ),
                    );
                  }
                      : null,
                  child: const Text("Continue"),
                ),
              ],
            )
          ],
        ),
      ),
    );
  }
}