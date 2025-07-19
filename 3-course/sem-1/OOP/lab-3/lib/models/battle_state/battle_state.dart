import 'package:lab/models/cell/cell.dart';
import 'package:lab/models/ship/ship.dart';

class BattleState {
  List<List<Cell>> playerMatrix;
  List<List<Cell>> computerMatrix;
  Ship? currentShip;
  bool isHorizontal;
  List<Ship> ships;

  BattleState({
    required this.playerMatrix,
    required this.computerMatrix,
    this.currentShip,
    required this.isHorizontal,
    required this.ships,
  });
}
