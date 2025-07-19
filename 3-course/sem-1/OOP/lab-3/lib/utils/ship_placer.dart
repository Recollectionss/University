import 'package:lab/models/cell/cell.dart';
import 'package:lab/models/ship/ship.dart';

class ShipPlacer {
  final List<List<Cell>> matrix;

  ShipPlacer(this.matrix);

  bool isPlacementValid(int startX, int startY, int shipSize, bool horizontal) {
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

  bool placeShip(int startX, int startY, Ship ship, bool horizontal) {
    if (!isPlacementValid(startX, startY, ship.size, horizontal)) {
      return false;
    }
    ship.isHorizontal = horizontal;

    for (int i = 0; i < ship.size; i++) {
      if (horizontal) {
        matrix[startX][startY + i].isOccupied = true;
        matrix[startX][startY + i].ship = ship;
      } else {
        matrix[startX + i][startY].isOccupied = true;
        matrix[startX + i][startY].ship = ship;
      }
    }

    return true;
  }
}
