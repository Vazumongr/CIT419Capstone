// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Capstone/CapstoneGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCapstoneGameModeBase() {}
// Cross Module References
	CAPSTONE_API UClass* Z_Construct_UClass_ACapstoneGameModeBase_NoRegister();
	CAPSTONE_API UClass* Z_Construct_UClass_ACapstoneGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Capstone();
// End Cross Module References
	void ACapstoneGameModeBase::StaticRegisterNativesACapstoneGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ACapstoneGameModeBase_NoRegister()
	{
		return ACapstoneGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ACapstoneGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACapstoneGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Capstone,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACapstoneGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "CapstoneGameModeBase.h" },
		{ "ModuleRelativePath", "CapstoneGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACapstoneGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACapstoneGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ACapstoneGameModeBase_Statics::ClassParams = {
		&ACapstoneGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ACapstoneGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ACapstoneGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ACapstoneGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ACapstoneGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ACapstoneGameModeBase, 2535713266);
	template<> CAPSTONE_API UClass* StaticClass<ACapstoneGameModeBase>()
	{
		return ACapstoneGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ACapstoneGameModeBase(Z_Construct_UClass_ACapstoneGameModeBase, &ACapstoneGameModeBase::StaticClass, TEXT("/Script/Capstone"), TEXT("ACapstoneGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACapstoneGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
