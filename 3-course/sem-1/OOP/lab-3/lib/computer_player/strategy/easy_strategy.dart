import 'package:lab/computer_player/dto/coordinates_dto.dart';
import 'package:lab/computer_player/strategy/game_strategy.dart';

class EasyStrategy extends GameStrategy{
  @override
  CoordinatesDTO findNextTarget() {

    Future.delayed(const Duration(seconds: 1));
    return CoordinatesDTO(x: random.nextInt(10), y: random.nextInt(10));
  }
}