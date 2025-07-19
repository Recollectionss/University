import 'package:flutter/material.dart';
import 'package:lab/models/ship/ship.dart';

class Cell {
  final int row;
  final int col;
  bool isShot;
  bool isOccupied;
  Color? color;
  Ship? ship;

  Cell({
    required this.row,
    required this.col,
    this.isShot = false,
    this.isOccupied = false,
    this.color,
    this.ship,
  });
}
