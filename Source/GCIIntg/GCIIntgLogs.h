// Copyright (C) 2023 owoDra

#pragma once

#include "Logging/LogMacros.h"

GCIINTG_API DECLARE_LOG_CATEGORY_EXTERN(LogGCII, Log, All);

#if !UE_BUILD_SHIPPING

#define GCIILOG(FormattedText, ...) UE_LOG(LogGCII, Log, FormattedText, __VA_ARGS__)

#define GCIIENSURE(InExpression) ensure(InExpression)
#define GCIIENSURE_MSG(InExpression, InFormat, ...) ensureMsgf(InExpression, InFormat, __VA_ARGS__)
#define GCIIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) ensureAlwaysMsgf(InExpression, InFormat, __VA_ARGS__)

#define GCIICHECK(InExpression) check(InExpression)
#define GCIICHECK_MSG(InExpression, InFormat, ...) checkf(InExpression, InFormat, __VA_ARGS__)

#else

#define GCIILOG(FormattedText, ...)

#define GCIIENSURE(InExpression) InExpression
#define GCIIENSURE_MSG(InExpression, InFormat, ...) InExpression
#define GCIIENSURE_ALWAYS_MSG(InExpression, InFormat, ...) InExpression

#define GCIICHECK(InExpression) InExpression
#define GCIICHECK_MSG(InExpression, InFormat, ...) InExpression

#endif