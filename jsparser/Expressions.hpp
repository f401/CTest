#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H 1

#include <memory>
#include <vector>

namespace jsparser {

enum class ExpressionType {
  Function,
  VarDeclare,
  Params,
  ConstVar,
  ReferenceVar,
  FunctionCall,
  Return
};

class Expression {
public:
  virtual ExpressionType type() = 0;
};

typedef std::vector<std::shared_ptr<Expression>> Holder;

class ParamDeclare : public Expression {
public:
  virtual ExpressionType type() override { return ExpressionType::Params; }

private:
  std::string_view param_type;
  std::string_view name;
};

class Statement : public Expression {
public:

  void add(Expression *expr) noexcept {
    this->subExpression.push_back(std::make_shared<Expression>(expr));
  }

private:
  Holder subExpression;
};

class FunctionStatement: public Statement {
public:
  virtual ExpressionType type() override { return ExpressionType::Function; }
private:
  std::vector<ParamDeclare> params;
};

class ValueExpression : public Expression {
public:
  virtual bool canUseAsValue() { return true; }
};

class VarDeclareExpression : public Expression {
public:
  virtual ExpressionType type() override { return ExpressionType::VarDeclare; }

  std::string_view &getName() { return this->name; }

  const std::string_view &getName() const { return this->name; }

private:
  std::string_view name;
  std::shared_ptr<ValueExpression> value;
};

class ConstValueExpression : public ValueExpression {
public:
  virtual ExpressionType type() override { return ExpressionType::ConstVar; }

private:
  std::string_view var;
};

class ValueReferenceExpression : public ValueExpression {
public:
  virtual ExpressionType type() override {
    return ExpressionType::ReferenceVar;
  }

private:
  std::string_view refId;
};

class FunctionCallExpression : public ValueExpression {
public:
  virtual ExpressionType type() override {
    return ExpressionType::FunctionCall;
  }

private:
  std::vector<std::shared_ptr<ValueExpression>> params;
  std::string_view functionName;
};

class ReturnExpression : public ValueExpression {
public:
  virtual ExpressionType type() override { return ExpressionType::Return; }
};

}; // namespace jsparser

#endif /* end of include guard: EXPRESSIONS_H */
