import 'dart:math';
import 'package:flutter/material.dart';
import 'package:lab/computer_player/dto/coordinates_dto.dart';
import 'package:lab/models/cell/cell.dart';

abstract class GameStrategy {
  late Random random = Random();

  late List<List<Cell>> playerMatrix;

  void initialize(List<List<Cell>> playerMatrix) {
    this.playerMatrix = playerMatrix;
  }

  CoordinatesDTO findNextTarget();
  void onHit(Offset hit) {}
  void onKill() {}
}
