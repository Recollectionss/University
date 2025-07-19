import 'package:flutter/cupertino.dart';

class LogoImageWidget extends StatelessWidget {

  const LogoImageWidget({
    super.key,
  });

  @override
  Widget build(BuildContext context) {
    return Padding(
        padding: const EdgeInsets.all(30.0),
        child: Image.asset('assets/logo.jpeg')
    );
  }
}