import 'package:flutter/material.dart';
import 'package:lab/computer_player/dto/coordinates_dto.dart';
import 'package:lab/computer_player/strategy/game_strategy.dart';
import 'package:lab/models/cell/cell.dart';
import 'package:lab/models/ship/ship.dart';
import 'package:lab/utils/ship_placer.dart';

class ComputerPlayer {
  final GameStrategy strategy;
  final List<List<Cell>> matrix = List.generate(
    10,
        (row) => List.generate(10, (col) => Cell(row: row, col: col,isOccupied: false, ship: null)),
  );
  final List<Ship> shipsForComputer = [
    Ship(size: 4, count: 1),
    Ship(size: 3, count: 2),
    Ship(size: 2, count: 3),
    Ship(size: 1, count: 4),
  ];

  ComputerPlayer({required this.strategy,required List<List<Cell>> userMatrix}){
    placeShipsForComputer();
    strategy.initialize(userMatrix);
  }

  CoordinatesDTO makeMove() {
    return strategy.findNextTarget();
  }

  void placeShipsForComputer() {
      final shipPlacer = ShipPlacer(matrix);

      for (var ship in shipsForComputer) {
        for (int i = 0; i < ship.count; i++) {
          bool placed = false;

          while (!placed) {
            int startX = strategy.random.nextInt(10);
            int startY = strategy.random.nextInt(10);
            bool horizontal = strategy.random.nextBool();

            placed = shipPlacer.placeShip(startX, startY, ship, horizontal);
          }
        }
      }
    }

  void onHit(Offset hit) {
   strategy.onHit(hit);
  }

  void onKill() {
   strategy.onKill();
  }
}
