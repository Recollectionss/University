#include "evaluator.hh"

namespace ast {

int32_t Evaluator::visit(const IntegerLiteral& e) {
  result = e.value_get();
  return result;
}

int32_t Evaluator::visit(const BinaryOperator& e) {
  e.left_get().accept(*this);
  int left = result;
  e.right_get().accept(*this);
  int right = result;

  switch (e.op_get()) {
    case BinaryOperator::Kind::ADD: result = left + right; break;
    case BinaryOperator::Kind::SUB: result = left - right; break;
    case BinaryOperator::Kind::MUL: result = left * right; break;
    case BinaryOperator::Kind::DIV:
      if (right == 0)
        utils::error(e.location_get(), "division by zero");
      result = left / right;
      break;
    case BinaryOperator::Kind::EQ: result = (left == right); break;
    case BinaryOperator::Kind::NEQ: result = (left != right); break;
    case BinaryOperator::Kind::LT: result = (left < right); break;
    case BinaryOperator::Kind::LE: result = (left <= right); break;
    case BinaryOperator::Kind::GT: result = (left > right); break;
    case BinaryOperator::Kind::GE: result = (left >= right); break;
    case BinaryOperator::Kind::AND: result = (left && right); break;
    case BinaryOperator::Kind::OR: result = (left || right); break;
    default:
      utils::error(e.location_get(), "unsupported binary operator");
  }

  return result;
}
