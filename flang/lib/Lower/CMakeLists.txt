get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(extension_libs GLOBAL PROPERTY MLIR_EXTENSION_LIBS)

add_flang_library(FortranLower
  Allocatable.cpp
  Bridge.cpp
  CallInterface.cpp
  Coarray.cpp
  ComponentPath.cpp
  ConvertArrayConstructor.cpp
  ConvertCall.cpp
  ConvertConstant.cpp
  ConvertExpr.cpp
  ConvertExprToHLFIR.cpp
  ConvertProcedureDesignator.cpp
  ConvertType.cpp
  ConvertVariable.cpp
  CustomIntrinsicCall.cpp
  HlfirIntrinsics.cpp
  HostAssociations.cpp
  IO.cpp
  IterationSpace.cpp
  LoweringOptions.cpp
  Mangler.cpp
  OpenACC.cpp
  OpenMP/ClauseProcessor.cpp
  OpenMP/Clauses.cpp
  OpenMP/DataSharingProcessor.cpp
  OpenMP/Decomposer.cpp
  OpenMP/OpenMP.cpp
  OpenMP/PrivateReductionUtils.cpp
  OpenMP/ReductionProcessor.cpp
  OpenMP/Utils.cpp
  PFTBuilder.cpp
  Runtime.cpp
  Support/Utils.cpp
  SymbolMap.cpp
  VectorSubscripts.cpp
  
  DEPENDS
  CUFAttrs
  CUFDialect
  FIRDialect
  FIRTransforms
  HLFIRDialect

  LINK_LIBS
  CUFAttrs
  CUFDialect
  FIRDialect
  FIRDialectSupport
  FIRBuilder
  FIRSupport
  FIRTransforms
  HLFIRDialect
  FortranSupport
  FortranParser
  FortranEvaluate
  FortranSemantics

  LINK_COMPONENTS
  Support

  MLIR_DEPS
  ${dialect_libs}
  ${extension_libs}

  MLIR_LIBS
  ${dialect_libs}
  ${extension_libs}
  MLIRAffineToStandard
  MLIRFuncDialect
  MLIRLLVMDialect
  MLIRSCFToControlFlow
)
