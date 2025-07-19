import 'package:flutter/material.dart';

class MatrixPainter extends CustomPainter {
  @override
  void paint(Canvas canvas, Size size) {
    final paint = Paint()
      ..color = Colors.white
      ..style = PaintingStyle.stroke;

    double cellSize = size.width / 10;

    for (int i = 0; i <= 10; i++) {
      canvas.drawLine(Offset(0, i * cellSize), Offset(size.width, i * cellSize), paint);
    }

    for (int i = 0; i <= 10; i++) {
      canvas.drawLine(Offset(i * cellSize, 0), Offset(i * cellSize, size.height), paint);
    }
  }

  @override
  bool shouldRepaint(covariant CustomPainter oldDelegate) {
    return true;
  }
}
