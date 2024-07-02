// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WutheringPlayer/Public/FirstCharacter_1.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFirstCharacter_1() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_WutheringPlayer();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_AFirstCharacter_1();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_AFirstCharacter_1_NoRegister();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_APlayer1();
// End Cross Module References

// Begin Class AFirstCharacter_1
void AFirstCharacter_1::StaticRegisterNativesAFirstCharacter_1()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFirstCharacter_1);
UClass* Z_Construct_UClass_AFirstCharacter_1_NoRegister()
{
	return AFirstCharacter_1::StaticClass();
}
struct Z_Construct_UClass_AFirstCharacter_1_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "FirstCharacter_1.h" },
		{ "ModuleRelativePath", "Public/FirstCharacter_1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_weaponMeshComp_MetaData[] = {
		{ "Category", "WeaponMesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb7\xef\xbf\xbd\xc5\xbb\xef\xbf\xbd\xde\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/FirstCharacter_1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xcc\xb7\xef\xbf\xbd\xc5\xbb\xef\xbf\xbd\xde\xbd\xef\xbf\xbd" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_weaponMeshComp;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFirstCharacter_1>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFirstCharacter_1_Statics::NewProp_weaponMeshComp = { "weaponMeshComp", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFirstCharacter_1, weaponMeshComp), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_weaponMeshComp_MetaData), NewProp_weaponMeshComp_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFirstCharacter_1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstCharacter_1_Statics::NewProp_weaponMeshComp,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFirstCharacter_1_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AFirstCharacter_1_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayer1,
	(UObject* (*)())Z_Construct_UPackage__Script_WutheringPlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFirstCharacter_1_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFirstCharacter_1_Statics::ClassParams = {
	&AFirstCharacter_1::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AFirstCharacter_1_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AFirstCharacter_1_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFirstCharacter_1_Statics::Class_MetaDataParams), Z_Construct_UClass_AFirstCharacter_1_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFirstCharacter_1()
{
	if (!Z_Registration_Info_UClass_AFirstCharacter_1.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFirstCharacter_1.OuterSingleton, Z_Construct_UClass_AFirstCharacter_1_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFirstCharacter_1.OuterSingleton;
}
template<> WUTHERINGPLAYER_API UClass* StaticClass<AFirstCharacter_1>()
{
	return AFirstCharacter_1::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFirstCharacter_1);
AFirstCharacter_1::~AFirstCharacter_1() {}
// End Class AFirstCharacter_1

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_FirstCharacter_1_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFirstCharacter_1, AFirstCharacter_1::StaticClass, TEXT("AFirstCharacter_1"), &Z_Registration_Info_UClass_AFirstCharacter_1, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFirstCharacter_1), 268766246U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_FirstCharacter_1_h_3622298625(TEXT("/Script/WutheringPlayer"),
	Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_FirstCharacter_1_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_FirstCharacter_1_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
