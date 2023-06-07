// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "MultiPlayerShootGame/Character/BlasterCharacter.h"

// AWeapon 类的构造函数
AWeapon::AWeapon()
{
	// 设置这个对象在每一帧都使用Tick函数。如果不需要，可以关闭以提高性能。
	PrimaryActorTick.bCanEverTick = false;
	// 设置对象具有网络复制功能
	bReplicates = true;

	// 创建武器的网格组件，并附加使用默认子对象
	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	// 将武器网格设置为根组件
	SetRootComponent(weaponMesh);

	// 设置武器网格与其他组件相碰时全部阻挡
	weaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	// 设置武器网格忽略碰撞到玩家控制角色的碰撞
	weaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// 禁用武器网格的碰撞检测功能
	weaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 创建碰撞区域的球体组件，并附加使用默认子对象
	areaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	// 附加区域球体到根组件
	areaSphere->SetupAttachment(RootComponent);
	// 设置区域球体忽略所有碰撞通道
	areaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// 禁用区域球体的碰撞功能
	areaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 如果具有权限（通常为服务端），设置以下属性(自己电脑控制的就是具有权限的，注意UE的单人模拟多人模式下其他两个模拟的客户端是没有权限的)
	if (HasAuthority()) {
		// 使区域球体的碰撞功能有效并执行查询和物理计算
		areaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// 使区域球体对影响到玩家控制角色的碰撞通道进行重叠
		areaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		areaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
	}

	pickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	pickupWidget->SetupAttachment(RootComponent);
}
 
// 当游戏开始或生成对象时，调用 BeginPlay 函数
void AWeapon::BeginPlay()
{
	// 调用 AActor 类所继承的基类的方法
	Super::BeginPlay();

	if (pickupWidget) {
		pickupWidget->SetVisibility(false);
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	ABlasterCharacter* blasterCharacter = Cast<ABlasterCharacter>(otherActor);
	if (blasterCharacter) {
		blasterCharacter->SetOverlappingWeapon(this);
	}
}

void AWeapon::ShowPickupWidget(bool bShowWidget)
{
	if (pickupWidget) {
		pickupWidget->SetVisibility(bShowWidget);
	}
}

