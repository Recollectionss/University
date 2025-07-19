class Ship {
  final int size;
  int count;
  bool isHorizontal; // Add this to track orientation

  Ship({required this.size, required this.count, this.isHorizontal = true});
}
