import 'package:flutter/material.dart';
import 'package:lab/computer_player/dto/coordinates_dto.dart';
import 'package:lab/computer_player/strategy/game_strategy.dart';
import 'dart:math';

class MiddleStrategy extends GameStrategy {
  final Set<Offset> visitedCells = {};
  final List<Offset> hitCells = [];
  final List<Offset> potentialTargets = [];
  final Random random = Random();
  Offset? lastHit;
  Offset? firstHit;
  Offset? currentDirection;

  @override
  CoordinatesDTO findNextTarget() {
    if (potentialTargets.isNotEmpty) {
      return _continueDirection();
    }
    if (lastHit != null) {
      return _findDirection();
    }
    return _generateRandomTarget();
  }

  CoordinatesDTO _generateRandomTarget() {
    int row, col;
    Offset randomTarget;

    do {
      row = random.nextInt(10);
      col = random.nextInt(10);
      randomTarget = Offset(col.toDouble(), row.toDouble());
    } while (visitedCells.contains(randomTarget));

    visitedCells.add(randomTarget);
    return CoordinatesDTO(x: col, y: row);
  }

  CoordinatesDTO _findDirection() {
    if (firstHit == null) {
      firstHit = lastHit;
      _addAdjacentCells(lastHit!);
    } else if (currentDirection != null) {
      final nextTarget = lastHit! + currentDirection!;
      if (_isValidCell(nextTarget)) {
        visitedCells.add(nextTarget);
        return CoordinatesDTO(x: nextTarget.dx.toInt(), y: nextTarget.dy.toInt());
      } else {
        currentDirection = -currentDirection!;
        lastHit = firstHit;
        return _findDirection();
      }
    } else {
      _determineDirection();
    }
    return _continueDirection();
  }

  CoordinatesDTO _continueDirection() {
    if (potentialTargets.isEmpty) {
      return _generateRandomTarget();
    }

    final target = potentialTargets.removeAt(0);
    visitedCells.add(target);
    return CoordinatesDTO(x: target.dx.toInt(), y: target.dy.toInt());
  }

  void _addAdjacentCells(Offset hit) {
    final directions = [
      Offset(0, -1), // Вгору
      Offset(0, 1),  // Вниз
      Offset(-1, 0), // Вліво
      Offset(1, 0),  // Вправо
    ];

    for (final dir in directions) {
      final neighbor = Offset(hit.dx + dir.dx, hit.dy + dir.dy);
      if (_isValidCell(neighbor)) {
        potentialTargets.add(neighbor);
      }
    }
  }

  void _determineDirection() {
    if (hitCells.length >= 2) {
      final first = hitCells[0];
      final second = hitCells[1];

      final dx = second.dx - first.dx;
      final dy = second.dy - first.dy;

      if ((dx.abs() == 0 || dy.abs() == 0) && (dx.abs() + dy.abs() == 1)) {
        currentDirection = Offset(dx, dy);
      }
    }
  }

  bool _isValidCell(Offset cell, {Offset? direction}) {
    final x = cell.dx.toInt();
    final y = cell.dy.toInt();

    if (direction != null) {
      final dx = (cell.dx - firstHit!.dx).toInt();
      final dy = (cell.dy - firstHit!.dy).toInt();
      if (dx * direction.dx + dy * direction.dy < 0) {
        return false;
      }
    }

    return x >= 0 && x < 10 && y >= 0 && y < 10 && !visitedCells.contains(cell);
  }

  void onKill() {
    lastHit = null;
    firstHit = null;
    currentDirection = null;
    final tempHitCells = List<Offset>.from(hitCells);
    hitCells.clear();
    _blockSurroundingCells(tempHitCells);
  }

  void _blockSurroundingCells(List<Offset> hits) {
    final directions = [
      Offset(0, -1), Offset(0, 1),
      Offset(-1, 0), Offset(1, 0),
    ];

    for (final hit in hits) {
      for (final dir in directions) {
        final neighbor = Offset(hit.dx + dir.dx, hit.dy + dir.dy);
        if (_isValidCell(neighbor)) {
          visitedCells.add(neighbor);
        }
      }
    }
  }
  @override
  void onHit(Offset hit) {
    hitCells.add(hit);
  }
}