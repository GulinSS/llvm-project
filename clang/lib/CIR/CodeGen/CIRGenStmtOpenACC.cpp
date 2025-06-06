//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Emit OpenACC Stmt nodes as CIR code.
//
//===----------------------------------------------------------------------===//

#include "CIRGenBuilder.h"
#include "CIRGenFunction.h"
#include "clang/AST/OpenACCClause.h"
#include "clang/AST/StmtOpenACC.h"

#include "mlir/Dialect/OpenACC/OpenACC.h"

using namespace clang;
using namespace clang::CIRGen;
using namespace cir;
using namespace mlir::acc;

namespace {
class OpenACCClauseCIREmitter final
    : public OpenACCClauseVisitor<OpenACCClauseCIREmitter> {
  CIRGenModule &cgm;

  void clauseNotImplemented(const OpenACCClause &c) {
    cgm.errorNYI(c.getSourceRange(), "OpenACC Clause", c.getClauseKind());
  }

public:
  OpenACCClauseCIREmitter(CIRGenModule &cgm) : cgm(cgm) {}

#define VISIT_CLAUSE(CN)                                                       \
  void Visit##CN##Clause(const OpenACC##CN##Clause &clause) {                  \
    clauseNotImplemented(clause);                                              \
  }
#include "clang/Basic/OpenACCClauses.def"
};
} // namespace

template <typename Op, typename TermOp>
mlir::LogicalResult CIRGenFunction::emitOpenACCComputeOp(
    mlir::Location start, mlir::Location end,
    llvm::ArrayRef<const OpenACCClause *> clauses,
    const Stmt *structuredBlock) {
  mlir::LogicalResult res = mlir::success();

  OpenACCClauseCIREmitter clauseEmitter(getCIRGenModule());
  clauseEmitter.VisitClauseList(clauses);

  llvm::SmallVector<mlir::Type> retTy;
  llvm::SmallVector<mlir::Value> operands;
  auto op = builder.create<Op>(start, retTy, operands);

  mlir::Block &block = op.getRegion().emplaceBlock();
  mlir::OpBuilder::InsertionGuard guardCase(builder);
  builder.setInsertionPointToEnd(&block);

  LexicalScope ls{*this, start, builder.getInsertionBlock()};
  res = emitStmt(structuredBlock, /*useCurrentScope=*/true);

  builder.create<TermOp>(end);
  return res;
}

mlir::LogicalResult
CIRGenFunction::emitOpenACCComputeConstruct(const OpenACCComputeConstruct &s) {
  mlir::Location start = getLoc(s.getSourceRange().getEnd());
  mlir::Location end = getLoc(s.getSourceRange().getEnd());

  switch (s.getDirectiveKind()) {
  case OpenACCDirectiveKind::Parallel:
    return emitOpenACCComputeOp<ParallelOp, mlir::acc::YieldOp>(
        start, end, s.clauses(), s.getStructuredBlock());
  case OpenACCDirectiveKind::Serial:
    return emitOpenACCComputeOp<SerialOp, mlir::acc::YieldOp>(
        start, end, s.clauses(), s.getStructuredBlock());
  case OpenACCDirectiveKind::Kernels:
    return emitOpenACCComputeOp<KernelsOp, mlir::acc::TerminatorOp>(
        start, end, s.clauses(), s.getStructuredBlock());
  default:
    llvm_unreachable("invalid compute construct kind");
  }
}

mlir::LogicalResult
CIRGenFunction::emitOpenACCLoopConstruct(const OpenACCLoopConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Loop Construct");
  return mlir::failure();
}
mlir::LogicalResult CIRGenFunction::emitOpenACCCombinedConstruct(
    const OpenACCCombinedConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Combined Construct");
  return mlir::failure();
}
mlir::LogicalResult
CIRGenFunction::emitOpenACCDataConstruct(const OpenACCDataConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Data Construct");
  return mlir::failure();
}
mlir::LogicalResult CIRGenFunction::emitOpenACCEnterDataConstruct(
    const OpenACCEnterDataConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC EnterData Construct");
  return mlir::failure();
}
mlir::LogicalResult CIRGenFunction::emitOpenACCExitDataConstruct(
    const OpenACCExitDataConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC ExitData Construct");
  return mlir::failure();
}
mlir::LogicalResult CIRGenFunction::emitOpenACCHostDataConstruct(
    const OpenACCHostDataConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC HostData Construct");
  return mlir::failure();
}
mlir::LogicalResult
CIRGenFunction::emitOpenACCWaitConstruct(const OpenACCWaitConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Wait Construct");
  return mlir::failure();
}
mlir::LogicalResult
CIRGenFunction::emitOpenACCInitConstruct(const OpenACCInitConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Init Construct");
  return mlir::failure();
}
mlir::LogicalResult CIRGenFunction::emitOpenACCShutdownConstruct(
    const OpenACCShutdownConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Shutdown Construct");
  return mlir::failure();
}
mlir::LogicalResult
CIRGenFunction::emitOpenACCSetConstruct(const OpenACCSetConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Set Construct");
  return mlir::failure();
}
mlir::LogicalResult
CIRGenFunction::emitOpenACCUpdateConstruct(const OpenACCUpdateConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Update Construct");
  return mlir::failure();
}
mlir::LogicalResult
CIRGenFunction::emitOpenACCAtomicConstruct(const OpenACCAtomicConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Atomic Construct");
  return mlir::failure();
}
mlir::LogicalResult
CIRGenFunction::emitOpenACCCacheConstruct(const OpenACCCacheConstruct &s) {
  getCIRGenModule().errorNYI(s.getSourceRange(), "OpenACC Cache Construct");
  return mlir::failure();
}
