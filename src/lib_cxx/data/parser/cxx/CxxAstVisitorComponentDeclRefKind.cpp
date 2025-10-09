#include "CxxAstVisitorComponentDeclRefKind.h"

CxxAstVisitorComponentDeclRefKind::CxxAstVisitorComponentDeclRefKind(CxxAstVisitor* astVisitor)
	: CxxAstVisitorComponent(astVisitor)
{
}

ReferenceKind CxxAstVisitorComponentDeclRefKind::getReferenceKind() const
{
	return m_thisRefKind;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseDecl(clang::Decl*  /*d*/)
{
	saveAll();
	m_thisRefKind = ReferenceKind::USAGE;
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::endTraverseDecl(clang::Decl*  /*d*/)
{
	restoreAll();
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseStmt(clang::Stmt* s)
{
	saveAll();

	if (s == nullptr)
	{
		return;
	}

	m_thisRefKind = m_childRefKind;
	if (!clang::isa<clang::Expr>(s))
	{
		m_thisRefKind = ReferenceKind::USAGE;
	}
	m_childRefKind = m_thisRefKind;
}

void CxxAstVisitorComponentDeclRefKind::endTraverseStmt(clang::Stmt*  /*s*/)
{
	restoreAll();
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseType(const clang::QualType&  /*t*/)
{
	saveAll();
	m_thisRefKind = ReferenceKind::USAGE;
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::endTraverseType(const clang::QualType&  /*t*/)
{
	restoreAll();
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseTypeLoc(const clang::TypeLoc&  /*tl*/)
{
	saveAll();
	m_thisRefKind = ReferenceKind::USAGE;
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::endTraverseTypeLoc(const clang::TypeLoc&  /*tl*/)
{
	restoreAll();
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseCallCommonCallee()
{
	m_thisRefKind = ReferenceKind::CALL;
	m_childRefKind = ReferenceKind::CALL;
}
void CxxAstVisitorComponentDeclRefKind::beginTraverseCallCommonArgument()
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseBinCommaLhs()
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseBinCommaRhs()
{
	m_childRefKind = m_thisRefKind;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseAssignCommonLhs()
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseAssignCommonRhs()
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseConstructorInitializer(
	clang::CXXCtorInitializer*  /*init*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseCXXTemporaryObjectExpr(
	clang::CXXTemporaryObjectExpr*  /*s*/)
{
	m_thisRefKind = ReferenceKind::CALL;
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::beginTraverseUnresolvedMemberExpr(clang::UnresolvedMemberExpr*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitVarDecl(clang::VarDecl*  /*d*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitCastExpr(clang::CastExpr* s)
{
	switch (s->getCastKind())
	{
	case clang::CK_ArrayToPointerDecay:
	case clang::CK_ToVoid:
	case clang::CK_LValueToRValue:
		m_childRefKind = ReferenceKind::USAGE;
	default:
		break;
	}
}

void CxxAstVisitorComponentDeclRefKind::visitUnaryAddrOf(clang::UnaryOperator*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitUnaryDeref(clang::UnaryOperator*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitDeclStmt(clang::DeclStmt*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitReturnStmt(clang::ReturnStmt*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitInitListExpr(clang::InitListExpr*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitMemberExpr(clang::MemberExpr*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::visitCXXDependentScopeMemberExpr(
	clang::CXXDependentScopeMemberExpr*  /*s*/)
{
	m_childRefKind = ReferenceKind::USAGE;
}

void CxxAstVisitorComponentDeclRefKind::saveAll()
{
	m_oldThisRefKinds.push_back(m_thisRefKind);
	m_oldChildRefKinds.push_back(m_childRefKind);
}

void CxxAstVisitorComponentDeclRefKind::restoreAll()
{
	m_thisRefKind = m_oldThisRefKinds.back();
	m_oldThisRefKinds.pop_back();

	m_childRefKind = m_oldChildRefKinds.back();
	m_oldChildRefKinds.pop_back();
}
