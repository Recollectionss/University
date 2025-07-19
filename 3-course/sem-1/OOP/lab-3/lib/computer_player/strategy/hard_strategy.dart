import 'package:flutter/material.dart';
import 'package:lab/computer_player/dto/coordinates_dto.dart';
import 'package:lab/computer_player/strategy/game_strategy.dart';

class HardStrategy extends GameStrategy {
  final List<List<int>> probabilityMap = List.generate(10, (_) => List.filled(10, 0));
  final Set<Offset> visitedCells = {};

  @override
  CoordinatesDTO findNextTarget() {
   return CoordinatesDTO(x: 0, y: 0);
  }
}

