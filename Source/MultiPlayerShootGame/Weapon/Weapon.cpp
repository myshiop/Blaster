// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "MultiPlayerShootGame/Character/BlasterCharacter.h"

// AWeapon ��Ĺ��캯��
AWeapon::AWeapon()
{
	// �������������ÿһ֡��ʹ��Tick�������������Ҫ�����Թر���������ܡ�
	PrimaryActorTick.bCanEverTick = false;
	// ���ö���������縴�ƹ���
	bReplicates = true;

	// �������������������������ʹ��Ĭ���Ӷ���
	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	// ��������������Ϊ�����
	SetRootComponent(weaponMesh);

	// �������������������������ʱȫ���赲
	weaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	// �����������������ײ����ҿ��ƽ�ɫ����ײ
	weaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// ���������������ײ��⹦��
	weaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ������ײ��������������������ʹ��Ĭ���Ӷ���
	areaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	// �����������嵽�����
	areaSphere->SetupAttachment(RootComponent);
	// ���������������������ײͨ��
	areaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// ���������������ײ����
	areaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// �������Ȩ�ޣ�ͨ��Ϊ����ˣ���������������(�Լ����Կ��Ƶľ��Ǿ���Ȩ�޵ģ�ע��UE�ĵ���ģ�����ģʽ����������ģ��Ŀͻ�����û��Ȩ�޵�)
	if (HasAuthority()) {
		// ʹ�����������ײ������Ч��ִ�в�ѯ���������
		areaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// ʹ���������Ӱ�쵽��ҿ��ƽ�ɫ����ײͨ�������ص�
		areaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		areaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
	}

	pickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	pickupWidget->SetupAttachment(RootComponent);
}
 
// ����Ϸ��ʼ�����ɶ���ʱ������ BeginPlay ����
void AWeapon::BeginPlay()
{
	// ���� AActor �����̳еĻ���ķ���
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

