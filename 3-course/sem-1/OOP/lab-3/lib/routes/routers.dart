import 'package:flutter/material.dart';
import 'package:lab/constants/constants.dart';
import 'package:lab/screens/screens.dart';

final Map<String, WidgetBuilder> routes = {
  Constants.HOMEPAGE: (context) => BaseScreen(
    nameButton1: "Battle",
    nameButton2: "Statistics",
    routeButton1: Constants.GAME_MODE,
    routeButton2: "/",
  ),
  Constants.GAME_MODE: (context) => BaseScreen(
    nameButton1: "1 player",
    nameButton2: "2 players",
    routeButton1: Constants.BATTLE_PREPARATION,
    routeButton2: "/",
  ),
  Constants.BATTLE_PREPARATION: (context) => const BattlePreparationScreen(),
};