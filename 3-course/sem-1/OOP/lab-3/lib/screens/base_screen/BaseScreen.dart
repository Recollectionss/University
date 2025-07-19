import 'package:flutter/material.dart';
import 'package:lab/components/button/button.dart';
import 'package:lab/components/logo/logo.dart';

class BaseScreen extends StatefulWidget {
  const BaseScreen({
    super.key,
    required this.nameButton1,
    required this.nameButton2,
    required this.routeButton1,
    required this.routeButton2,
  });
  final String nameButton1;
  final String nameButton2;
  final String routeButton1;
  final String routeButton2;

  @override
  State<BaseScreen> createState() => _BaseScreenState();
}

class _BaseScreenState extends State<BaseScreen> {


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor:Colors.white,
      appBar: AppBar(
        backgroundColor: Color.fromARGB(255, 9, 41, 104),
      ),
      body: Center(
        child: Builder(
          builder: (context) {
            return Column(
                children: [
                  const LogoImageWidget(),
                  const SizedBox(height: 150,),
                  Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      CustomButtonWidget(name: widget.nameButton1, route: widget.routeButton1),
                      // const SizedBox(width: 24),
                      // CustomButtonWidget(name: widget.nameButton2, route: widget.routeButton2),

                    ],
                  )
                ]
            );
          },
        ),
      ),
    );
  }
}