import 'package:flutter/material.dart';

class CustomButtonWidget extends StatelessWidget {
  final String name;
  final String route;

  const CustomButtonWidget({
    required this.name,
    required this.route,
    super.key,
  });

  @override
  Widget build(BuildContext context) {
    return ElevatedButton(
      onPressed: () {
        Navigator.pushNamed(context, route);
      },
      child: Text(
        name,
        style: const TextStyle(fontSize: 25),
      ),
    );
  }
}
