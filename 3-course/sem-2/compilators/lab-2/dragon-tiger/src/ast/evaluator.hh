#pragma once

#include "nodes.hh"
#include "../utils/errors.hh"

namespace ast {

class Evaluator : public ConstASTIntVisitor {
public:
  int result;

  Evaluator() : result(0) {}

  int32_t visit(const IntegerLiteral& e) {
  result = e.accept();
  return result;
  };
  int32_t visit(const BinaryOperator& e) {
  e.get_left().accept(*this);
  int left = result;
  e.get_right().accept(*this);
  int right = result;

  switch (e.get_type()) {
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
};
  int32_t visit(const Sequence& e) {
  if (e.accept().empty())
    utils::error(e.get_exprs(), "empty sequence");

  for (auto* expr : e.accept())
    expr->accept(*this);

  return result;
};
  int32_t visit(const IfThenElse& e) {
  e.().accept(*this);
  if (result) {
    e.then_get().accept(*this);
  } else {
    if (e.else_has())
      e.else_get().accept(*this);
    else
      result = 0;
  }

  return result;
};

  int32_t visit(const StringLiteral& e) override { utils::error("cannot evaluate StringLiteral"); return 0; }
  int32_t visit(const Let& e) override { utils::error("cannot evaluate Let"); return 0; }
  int32_t visit(const Identifier& e) override { utils::error("cannot evaluate Identifier"); return 0; }
  int32_t visit(const VarDecl& e) override { utils::error("cannot evaluate VarDecl"); return 0; }
  int32_t visit(const FunDecl& e) override { utils::error("cannot evaluate FunDecl"); return 0; }
  int32_t visit(const FunCall& e) override { utils::error("cannot evaluate FunCall"); return 0; }
  int32_t visit(const WhileLoop& e) override { utils::error("cannot evaluate WhileLoop"); return 0; }
  int32_t visit(const ForLoop& e) override { utils::error("cannot evaluate ForLoop"); return 0; }
  int32_t visit(const Break& e) override { utils::error("cannot evaluate Break"); return 0; }
  int32_t visit(const Assign& e) override { utils::error("cannot evaluate Assign"); return 0; }

  ~Evaluator() override = default;
};

}
