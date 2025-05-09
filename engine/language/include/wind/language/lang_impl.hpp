#pragma once
#include "nodes/FunctionArgumentStatement.hpp"
#include "nodes/AssignStatement.hpp"
#include "nodes/BinaryOperation.hpp"
#include "nodes/ClassMember.hpp"
#include "nodes/ClassStatement.hpp"
#include "nodes/ForStatement.hpp"
#include "nodes/FunctionStatement.hpp"
#include "nodes/Identifier.hpp"
#include "nodes/IfStatement.hpp"
#include "nodes/ImportStatement.hpp"
#include "nodes/InvokeExpression.hpp"
#include "nodes/ReturnStatement.hpp"
#include "nodes/UnaryOperation.hpp"
#include "nodes/Value.hpp"
#include "nodes/VariableStatement.hpp"

namespace wind {
  class LangImpl {
  public:
    virtual ~LangImpl() = default;
    virtual void compile(wdlang::Value*) = 0;
    virtual void compile(wdlang::Identifier*) = 0;
    virtual void compile(wdlang::UnaryOperation*) = 0;
    virtual void compile(wdlang::BinaryOperation*) = 0;
    virtual void compile(wdlang::AssignStatement*) = 0;
    virtual void compile(wdlang::VariableStatement*) = 0;
    virtual void compile(wdlang::ClassMember*) = 0;
    virtual void compile(wdlang::ClassStatement*) = 0;
    virtual void compile(wdlang::FunctionArgumentStatement*) = 0;
    virtual void compile(wdlang::FunctionStatement*) = 0;
    virtual void compile(wdlang::ReturnStatement*) = 0;
    virtual void compile(wdlang::ImportStatement*) = 0;
    virtual void compile(wdlang::InvokeExpression*) = 0;
    virtual void compile(wdlang::IfStatement*) = 0;
    virtual void compile(wdlang::ForStatement*) = 0;
  };
} // namespace wind

namespace wind::wdlang {
  template <typename Derived>
  void NodeCRTP<Derived>::execute(LangImpl* executor) {
    executor->compile(static_cast<Derived*>(this));
  }
} // namespace wind::wdlang
