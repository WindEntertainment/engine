#pragma once
#include "nodes/FunctionArgumentStatement.hpp"
#include "nodes/AssignStatement.hpp"
#include "nodes/BinaryOperation.hpp"
#include "nodes/ClassMember.hpp"
#include "nodes/ClassStatement.hpp"
#include "nodes/FunctionStatement.hpp"
#include "nodes/Identifier.hpp"
#include "nodes/ReturnStatement.hpp"
#include "nodes/UnaryOperation.hpp"
#include "nodes/Value.hpp"
#include "nodes/VariableStatement.hpp"

namespace wind {
  class LangImpl {
  public:
    virtual ~LangImpl() = default;
    virtual void compile(wind::wdlang::Value*) = 0;
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
  };
}