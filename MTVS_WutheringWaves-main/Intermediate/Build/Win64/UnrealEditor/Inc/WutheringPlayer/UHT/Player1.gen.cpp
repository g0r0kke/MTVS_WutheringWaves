// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WutheringPlayer/Public/Player1.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlayer1() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_APawn_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
UPackage* Z_Construct_UPackage__Script_WutheringPlayer();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_APlayer1();
WUTHERINGPLAYER_API UClass* Z_Construct_UClass_APlayer1_NoRegister();
// End Cross Module References

// Begin Class APlayer1
void APlayer1::StaticRegisterNativesAPlayer1()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APlayer1);
UClass* Z_Construct_UClass_APlayer1_NoRegister()
{
	return APlayer1::StaticClass();
}
struct Z_Construct_UClass_APlayer1_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Player1.h" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_springArmComp_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tpsCamComp_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_imc_Player_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_Look_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_Move_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_walkSpeed_MetaData[] = {
		{ "Category", "PlayerSetting" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xcc\xb5\xef\xbf\xbd \xef\xbf\xbd\xd3\xb5\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/Player1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xcc\xb5\xef\xbf\xbd \xef\xbf\xbd\xd3\xb5\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_Jump_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_Dash_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_Attack_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_Skill_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_SwitchTo1_MetaData[] = {
		{ "Category", "Input" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_inp_SwitchTo2_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd 1\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc8\xaf\n" },
#endif
		{ "ModuleRelativePath", "Public/Player1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd 1\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc8\xaf" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BP_Player1_MetaData[] = {
		{ "Category", "Characters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "ModuleRelativePath", "Public/Player1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xc4\xb3\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc6\xae \xc5\xac\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BP_Player2_MetaData[] = {
		{ "Category", "Characters" },
		{ "ModuleRelativePath", "Public/Player1.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_springArmComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tpsCamComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_imc_Player;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_Look;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_Move;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_walkSpeed;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_Jump;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_Dash;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_Attack;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_Skill;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_SwitchTo1;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inp_SwitchTo2;
	static const UECodeGen_Private::FClassPropertyParams NewProp_BP_Player1;
	static const UECodeGen_Private::FClassPropertyParams NewProp_BP_Player2;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlayer1>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_springArmComp = { "springArmComp", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, springArmComp), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_springArmComp_MetaData), NewProp_springArmComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_tpsCamComp = { "tpsCamComp", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, tpsCamComp), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tpsCamComp_MetaData), NewProp_tpsCamComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_imc_Player = { "imc_Player", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, imc_Player), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_imc_Player_MetaData), NewProp_imc_Player_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Look = { "inp_Look", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_Look), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_Look_MetaData), NewProp_inp_Look_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Move = { "inp_Move", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_Move), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_Move_MetaData), NewProp_inp_Move_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_walkSpeed = { "walkSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, walkSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_walkSpeed_MetaData), NewProp_walkSpeed_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Jump = { "inp_Jump", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_Jump), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_Jump_MetaData), NewProp_inp_Jump_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Dash = { "inp_Dash", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_Dash), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_Dash_MetaData), NewProp_inp_Dash_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Attack = { "inp_Attack", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_Attack), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_Attack_MetaData), NewProp_inp_Attack_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Skill = { "inp_Skill", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_Skill), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_Skill_MetaData), NewProp_inp_Skill_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_SwitchTo1 = { "inp_SwitchTo1", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_SwitchTo1), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_SwitchTo1_MetaData), NewProp_inp_SwitchTo1_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_inp_SwitchTo2 = { "inp_SwitchTo2", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, inp_SwitchTo2), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_inp_SwitchTo2_MetaData), NewProp_inp_SwitchTo2_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_BP_Player1 = { "BP_Player1", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, BP_Player1), Z_Construct_UClass_UClass, Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BP_Player1_MetaData), NewProp_BP_Player1_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_APlayer1_Statics::NewProp_BP_Player2 = { "BP_Player2", nullptr, (EPropertyFlags)0x0044000000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APlayer1, BP_Player2), Z_Construct_UClass_UClass, Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BP_Player2_MetaData), NewProp_BP_Player2_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APlayer1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_springArmComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_tpsCamComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_imc_Player,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Look,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Move,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_walkSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Jump,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Dash,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Attack,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_Skill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_SwitchTo1,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_inp_SwitchTo2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_BP_Player1,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APlayer1_Statics::NewProp_BP_Player2,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayer1_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APlayer1_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_WutheringPlayer,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APlayer1_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APlayer1_Statics::ClassParams = {
	&APlayer1::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_APlayer1_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_APlayer1_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APlayer1_Statics::Class_MetaDataParams), Z_Construct_UClass_APlayer1_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APlayer1()
{
	if (!Z_Registration_Info_UClass_APlayer1.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlayer1.OuterSingleton, Z_Construct_UClass_APlayer1_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APlayer1.OuterSingleton;
}
template<> WUTHERINGPLAYER_API UClass* StaticClass<APlayer1>()
{
	return APlayer1::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APlayer1);
APlayer1::~APlayer1() {}
// End Class APlayer1

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlayer1, APlayer1::StaticClass, TEXT("APlayer1"), &Z_Registration_Info_UClass_APlayer1, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlayer1), 1059953973U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1_h_740611322(TEXT("/Script/WutheringPlayer"),
	Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Admin_Documents_GitHub_MTVS_WutheringWaves_MTVS_WutheringWaves_main_Source_WutheringPlayer_Public_Player1_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
