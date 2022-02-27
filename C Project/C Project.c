/* 

Bu proje verilen test_system.txt dosyasindan bilgilieri okuyarak baslar. indirici(trafo), musteri kimlik numarasi,hat numarasi gibi bilgileri almaktadir. 
Klavyeden girilen hat numarasina ve musteri numarasina gore koordinatlarini veren, musterinin hangi tipte(mesken,sanayi,ticari) oldugunu tespit edebilen,
musteriler arasinda kus ucusu mesafeyi hesaplayabilen, en sonunda ise hatlar arasinda kopuk hatin hangisi oldugunu bulup dosyaya yazan bir projedir.

*/

#include <stdio.h>
#include <math.h>
#define SIZE 64

struct indirici{
	int ID;
	double x1,y1;
	double x2,y2;
};
typedef struct indirici indirici;

struct musteri{
	int ID;
	int TIP;
	double x1,y1;
	double x2,y2;
};
typedef struct musteri musteri;

struct hat{
	int ID;
	double x1,y1;
	double x2,y2;
};
typedef struct hat hat;

void hatSayisiBastir(int hatSayisi,hat hatlar[]);
void hatBilgisi(int hatSayisi,hat hatlar[]);
void musteriBilgisi(int musteriSayisi,musteri musteriler[]);
void indiriciBilgi(int hatSayisi,indirici indiriciler[]);
void musteriSayisiTipi(int musteriSayisi,musteri musteriler[]);
void kopukHat(int hatSayisi,hat hatlar[]);
void gosterHatSirasi(hat hatlar[],int hatSayisi);
void kusUcusuMesafe(musteri musteriler[],int musteriSayisi,indirici birIndirici);
void musteriHatUzunlugu(indirici birIndirici,musteri musteriler[],hat hatlar[],int musteriSayisi,int hatSayisi);

int main(){
	indirici indiriciler[SIZE];
	musteri musteriler[SIZE];
	hat hatlar[SIZE];
	int indiriciSayisi=0;
	int musteriSayisi=0;
	int hatSayisi=0;
	
	FILE *filep = fopen("test_system.txt","r");
	if(filep == NULL){
		printf("Dosya acilamadi.");
		return 1;
	}
	
	int quit=0;
	char line[SIZE];
	fgets(line,SIZE,filep);
	int i=0;
	while(! quit ){
		++indiriciSayisi;
		fgets(line,SIZE,filep);
		quit = ! sscanf(line,"%d%lf%lf%lf%lf",
		&indiriciler[i].ID,
		&indiriciler[i].x1,
		&indiriciler[i].y1,
		&indiriciler[i].x2,
		&indiriciler[i].y2);
		++i;
	}
	--indiriciSayisi;
	
	fgets(line,SIZE,filep);
	i=0;
	quit = 0;
	while(! quit){
		++musteriSayisi;
		fgets(line,SIZE,filep);
		quit = ! sscanf(line,"%d%d%lf%lf%lf%lf",
		&musteriler[i].ID,
		&musteriler[i].TIP,
		&musteriler[i].x1,
		&musteriler[i].y1,
		&musteriler[i].x2,
		&musteriler[i].y2) ;
		++i;
	}
	--musteriSayisi;
	
	fgets(line,SIZE,filep);
	i=0;
	quit = 0;
	while(! quit){
		++hatSayisi;
		fgets(line,SIZE,filep);
		quit = ! sscanf(line,"%d%lf%lf%lf%lf",
		&hatlar[i].ID,
		&hatlar[i].x1,
		&hatlar[i].y1,
		&hatlar[i].x2,
		&hatlar[i].y2) ;
		++i;
	}
	--hatSayisi;
	
	hatSayisiBastir(hatSayisi,hatlar);
	hatBilgisi(hatSayisi,hatlar);
	musteriBilgisi(musteriSayisi,musteriler);
	indiriciBilgi(hatSayisi,indiriciler);
	musteriSayisiTipi(musteriSayisi,musteriler);
	kopukHat(hatSayisi,hatlar);
	gosterHatSirasi(hatlar,hatSayisi);
	kusUcusuMesafe(musteriler,musteriSayisi,indiriciler[0]);
	musteriHatUzunlugu(indiriciler[0],musteriler,hatlar,musteriSayisi,hatSayisi);
	
}
void hatSayisiBastir(int hatSayisi,hat hatlar[]){
	double mesafe=0;
	int i;
	for( i=0 ; i<hatSayisi; ++i)
		mesafe += sqrt( pow( (hatlar[i].y2-hatlar[i].y1),2) + pow((hatlar[i].x2-hatlar[i].x1),2) );
		printf("Hat sayisi %d, Toplam hat uzunlugu %lf\n",hatSayisi,mesafe);
}

void hatBilgisi(int hatSayisi,hat hatlar[]){
	int ID;
	int i;
	printf("Hat ID : ");
	scanf("%d",&ID);
	for( i=0; i<hatSayisi; ++i){
		if(hatlar[i].ID == ID){
			printf("%lf %lf %lf %lf\n",hatlar[i].x1,hatlar[i].y1,hatlar[i].x2,hatlar[i].y2);
			i = hatSayisi;
		}
	}	
}

void musteriBilgisi(int musteriSayisi,musteri musteriler[]){
	int ID,i;
	printf("Musteri ID: ");
	scanf("%d",&ID);
	for( i=0; i<musteriSayisi; ++i){
		if(musteriler[i].ID == ID){
			
			printf("%lf %lf %lf %lf \n",musteriler[i].x1,musteriler[i].y1,musteriler[i].x2,musteriler[i].y2);
			if(musteriler[i].TIP == 1)
				printf("Mesken: %d\n",musteriler[i].ID);
			if(musteriler[i].TIP == 2)
				printf("Ticari: %d\n",musteriler[i].ID);
			if(musteriler[i].TIP == 3)
				printf("Sanayi: %d\n",musteriler[i].ID);
			
			i = musteriSayisi;
			
		}
	}
}

void indiriciBilgi(int hatSayisi,indirici indiriciler[]){
	int ID;
	int i;
	printf("Indirici ID : ");
	scanf("%d",&ID);
	for( i=0; i<hatSayisi; ++i){
		if(indiriciler[i].ID == ID){
			printf("%lf %lf %lf %lf\n",indiriciler[i].x1,indiriciler[i].y1,indiriciler[i].x2,indiriciler[i].y2);
			i = hatSayisi;
		}
	}
}

void musteriSayisiTipi(int musteriSayisi,musteri musteriler[]){
	int tip1=0,tip2=0,tip3=0;
	int i;
	for( i=0 ; i<musteriSayisi ; ++i){
		if(musteriler[i].TIP == 1)
			++tip1;
		if(musteriler[i].TIP == 2)
			++tip2;
		if(musteriler[i].TIP == 3)
			++tip3;
	}
	printf("Musteri sayisi : %d, Mesken : %d, Ticari : %d , Sanayi : %d\n",musteriSayisi,tip1,tip2,tip3);
}

void kopukHat(int hatSayisi,hat hatlar[]){
	
	FILE *fp;
	fp = fopen("Kopuk_hat_listesi.txt","w");
	int i;
	for( i=0 ; i<hatSayisi-1 ; ++i){
		if(hatlar[i].x2 != hatlar[i+1].x1 ||  hatlar[i].y2 != hatlar[i+1].y1){
			fprintf(fp,"Kopuk hat ID : %d\n",hatlar[i+1].ID);
			i = hatSayisi;
		}
	}
}

void gosterHatSirasi(hat hatlar[],int hatSayisi){
	
	FILE *pfile;
	pfile = fopen("Hat_Guzergah.txt","w");
	int i,hedef;
	printf("Hedef ID : ");
	scanf("%d",&hedef);
	fprintf(pfile,"HAT_GUZERGAHI\n");
	hat hedefHat;
	for( i=0 ; i<hatSayisi ; ++i){
		if(hedef == hatlar[i].ID){
			hedefHat = hatlar[i];
			i=hatSayisi;
		}
	}
	
	for( i=0 ; i<hatSayisi ; ++i){
		fprintf(pfile,"%d ",hatlar[i].ID);
		if(hedefHat.x1 == hatlar[i].x1 && hedefHat.y1 == hatlar[i].y1){
			fprintf(pfile,"%d ",hatlar[i+1].ID);
			i=hatSayisi;		
		}
			else if(hedefHat.x1 == hatlar[i].x2 && hedefHat.y1 == hatlar[i].y2){
			fprintf(pfile,"%d ",hatlar[i+1].ID);
			i=hatSayisi;
			}
	}
}

void kusUcusuMesafe(musteri musteriler[],int musteriSayisi,indirici birIndirici){
	
	FILE *pf;
	pf = fopen("Musteri_kus_ucusu_mesafe.txt","w");
	int i;
	double mesafe = 0.0;
	fprintf(pf,"ID\tTIP\tKUS_UCUSU_MESAFE\n");
	for( i=0 ; i<musteriSayisi ; ++i){
		mesafe = sqrt( pow( (musteriler[i].x1-birIndirici.x1),2) + pow((musteriler[i].y1-birIndirici.y1),2) );
		fprintf(pf,"%d\t%d\t%lf\n",musteriler[i].ID,musteriler[i].TIP,mesafe);
	}
}

void musteriHatUzunlugu(indirici birIndirici,musteri musteriler[],hat hatlar[],int musteriSayisi,int hatSayisi){
	
	FILE *fpp;
	
	fpp = fopen("Musteri_hat_uzunlugu.txt","w");
	
	int i,j;
	double mesafe = 0.0;
	fprintf(fpp,"HAT_UZUNLUGU\n");
	for( i=0 ; i<musteriSayisi ; ++i){
		for(j=0 ; j<hatSayisi ; ++j){
			
			mesafe += sqrt( pow( (hatlar[j].y2-hatlar[j].y1),2) + pow((hatlar[j].x2-hatlar[j].x1),2) );
			
			if(musteriler[i].x1 == hatlar[j].x2 && musteriler[i].y1 == hatlar[j].y2 ){
				fprintf(fpp,"%lf\n",mesafe);
				j = hatSayisi;
				mesafe = 0.0;
			}
		}
	}
}
