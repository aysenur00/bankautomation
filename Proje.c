#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>                                                    //25. grup banka otomasyonu
#include <locale.h>
                                                                     /* ismail acar 201180037 */
                                                                     /* ayþenur yavaþoðlu 201180024 */
typedef struct{                                                      /* Mehmet Emin AYAZ 191180013 */
    char isim[50];
    char Soyad[50];
    int MusteriNo;
    char dyeri[50];
    char tc[50];
    int HesapNo;
    float Bakiye;
}kullanici;

void MusteriEkleme()
{

	FILE *fpmusteri;
	    kullanici musteri;

		//Müþteri bilgilerinin isteneceðine dair bilgilendiriliyor.
		printf("Bankamýza hoþ geldiniz.Lütfen bilgilerinizi giriniz.\n");

		//Müþteriden adý alýnýyor.
		printf("Ad:");
		scanf("%s",musteri.isim);

		//Müþteriden soyadý alýnýyor.
		printf("Soyad:");
		scanf("%s",musteri.Soyad);

		//Müþteriden doðum yeri bilgisi alýnýyor.
		printf("Dogum yeri:");
		scanf("%s",musteri.dyeri);

		//Müþteriden tc kimlik no bilgisi alýnýyor.
		printf("TC:");
		scanf("%s",musteri.tc);

		//Müþteriye sistem tarafýndan rastgele müþteri numarasý atanýyor ve müþteriye bildiriliyor.
		printf("Musteri numarasi:");
		musteri.MusteriNo=rand()%100+100;
		printf("%d",musteri.MusteriNo);

		//Dosya iþlemleri için musteriler.txt dosyasý açýlýyor (Üstüne yazma modunda).
		fpmusteri=fopen("musteriler.txt","a");


		//fprintf fonksiyonu ile müþteriden aldýðýmýz bilgiler istediðimiz þekilde dosyaya yazýlýyor.
		fprintf(fpmusteri,"\n%d %s %s %s %s",musteri.MusteriNo,musteri.isim,musteri.Soyad,musteri.dyeri,musteri.tc);

		//Dosya kapanýyor.
		fclose(fpmusteri);

	}



void HesapAcma()
{
    kullanici Hesap;
    kullanici musteri;
    int musteriNo,secim;
    FILE *fpHesap,*fp1;

    //Hesaplar dosyasýný üstüne yazma moduyla açýyoruz.
    fpHesap=fopen("hesaplar.txt","a");

	//Müþteri kararýný deðiþtirmiþse menüye dönebilmesi için bir seçenek sunuluyor.
    printf("\nDevam etmek için->1 e basýnýz menüye dönmek için ->2\n");
    scanf("%d",&secim);

	//Müþterinin seçimine göre karar mekanizmalarý çalýþýyor.
    if(secim==1)
    {
        int say=0;

        //musteriler.txt dosyasý okuma modunda açýlýyor.
        fp1=fopen("musteriler.txt","r");

        //Müþteriden kendisine sistem tarafýndan atanmýþ olan müþteri numarasý isteniyor.
        printf("Lutfen musteri no girin:");
        scanf("%d",&musteriNo);

        //Okuma modunda açtýðýmýz dosyadaki kayýtlý bilgileri alýyoruz.
	    while(!feof(fp1))
	    {
	        fscanf(fp1,"\n%d %s %s %s %s ",&musteri.MusteriNo,&musteri.isim,&musteri.Soyad,&musteri.dyeri,&musteri.tc);

	        //Eðer müþterinin girdiði müþteri no dosyadan okuduðumuz müþteri no ile uyuþuyorsa çalýþýyor.
		    if(musteri.MusteriNo==musteriNo)
            {

            	//Müþteriye hesap bilgileri gösteriliyor.
                printf("\n%d %s %s %s %s ",musteri.MusteriNo,musteri.isim,musteri.Soyad,musteri.dyeri,musteri.tc);
		        ++say;

				//Müþteri bilgilendirmesi.
                printf("\nHesabiniz dogrulandi.Hesap acma islemi devam ediyor.");

				//Müþteriye sistem tarafýndan rastgele bir hesap numarasý veriliyor.
                Hesap.HesapNo=rand()%100+100;
                printf("\nHesap numaraniz: %d",Hesap.HesapNo);

                //Müþteriden ilk bakiyesi isteniyor (0'dan baþlatmak yerine müþteri istediði bakiyeyle hesabýný açabiliyor.).
                printf("\nIlk bakiyenizi giriniz:");
                scanf("%f",&Hesap.Bakiye);

				//Müþteri bilgilendirmesi.
                printf("\nIslem tamamlandi.Iyi gunler dileriz.");

				//Müþteriden aldýðýmýz bilgileri hesaplar dosyasýna istediðimiz þekilde kaydediyoruz.
                fprintf(fpHesap,"\n%d %s %s %.2f",Hesap.HesapNo,musteri.isim,musteri.Soyad,Hesap.Bakiye);

            }
	    }

	    //Dosyalarla iþimiz bittiðinden onlarý kapatýyoruz.
		fclose(fp1);
		fclose(fpHesap);

		/*Fonksiyonun baþýnda 0 olarak atadýðýmýz say deðiþkenimiz eðer yukarýdaki if bloðuna girseydi say++ komutuyla 1 artacaktý ve 0 olmayacaktý dolayýsýyla bu kod çalýþmayacaktý.
		Yani yukarýdaki if bloðuna giren durumlar (ki bu durumlar doðrulanmanýn saðlandýðý durumlardýr) say deðiþkenimizi artýrarak 0 olmaktan kurtarýyor.
		Böylece alttaki if bloðuna girmeyecek. Fakat eðer ki üstteki if bloðuna girilmemiþse yani müþteriden alýnan müþteri no ile dosyadaki müþteri no tutmuyor ise
		o zaman say++ komutu çalýþmamýþ olacak ve say=0 olarak kaldýðýndan bu bloða girilecek.*/
	    if(say==0)
	    {
	    	//Müþteri bilgilendirmesi
	    	printf("\nHesap dogrulanamadi!!!");

		}


	}
}

void ParaCekme()
{
	 kullanici Hesap;
     // deðiþkenlerin atandýðý kýsým
    float miktar,bakiye1;
    int HesapNumarasi,HesapNumarasi2,say1=0;
	int satir=0,satir2,temp=0;
	char *ad,*soyad;

        // hesap dosyasýnýn ve iþlemlerin üzerine yazýlýp hesap dosyasýnýn yerine geçecek geçici dosyanýn pointerlarý atanýyor
        FILE *fpHesap,*fpGecici;

        fpHesap=fopen("hesaplar.txt","r");
		//kullanýcýdan iþlem yapýlacak hesap numarasý isteniyor
        printf("\nLutfen hesap numarasi girin:");
        scanf("%d",&HesapNumarasi);

        //dosyanýn sonuna kadar okuma iþlemi gerçekleþtirilmesi için feof kullanýlýr
        while(!feof(fpHesap))
	    {
	        satir++;
		    fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);   //okuma iþlemleri

	    	if(Hesap.HesapNo==HesapNumarasi)
	    	{
		        say1++;
                satir2=satir;
                HesapNumarasi2=Hesap.HesapNo;
		        bakiye1=Hesap.Bakiye;                                       /* Hesaba ait deðerler iþlemlerin yapýlmasý için baþka deðiþkenlere atanýr*/
		        ad=Hesap.isim;
		        soyad=Hesap.Soyad;
		    	printf("\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,bakiye1);         //ekrana kullanýcýnýn bilgileri yazdýrýlýr/
		    	printf("\nHesap numarasi dogrulandi.Isleminiz devam ediyor.");
            }
        }
		fclose(fpHesap);
		// eðer girilen  hesap numarasý bulunmuyorsa say1 deðiþkeni üstteki if bloðuna girmediði için 0 kalýr böylece hesap numarasýnýn doðruluðu kontrol edilmiþ olur.
        if(say1==0)
        {
            printf("Hesap dogrulanamadi!!!");
            printf("\nCikis yapiliyor.");
            exit(0);

        }
         //müþteriden çekilecek tutar alýnýr
	    printf("\nCekmek istediginiz tutari giriniz:");
        scanf("%f",&miktar);
		// çekilecek miktar bakiyeden daha fazla olursa iþlem gerçekleþmez
        if(miktar>bakiye1)
		{
            printf("Bakiyeniz yetersizdir.");

		}
       //miktar küçükse hesaptan para çekme iþlemi gerçekleþir
        if(miktar<=bakiye1)
        {
            bakiye1=bakiye1-miktar;
            //çekilen miktar ve kalan para ekrana yazdýrýlýr
            printf("\n%.2f TL para cekildi.Kalan bakiye:%.2f",miktar,bakiye1);
            fpHesap=fopen("hesaplar.txt","r");
            //geçici bir dosya açýlýr
            fpGecici=fopen("gecici.txt","a");

            while(!feof(fpHesap))
            {
                temp++;
                fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);

                //eðer hesap numarasý doðru deðilse iþleme girmez yani deðerleri baþka deðiþkene atanmaz ve olduðu gibi gecici dosyasýna yazdýrýlýr
              if(satir2!=temp)
                {
                    fprintf(fpGecici,"\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);
                }

                //eðer hesap numarasý doðruysa iþleme girer ve yeni deðerler üzerinde iþlem yapýlan deðiþkenler vasýtasýyla gecici dosyasýna yazdýrýlýr.

                if(satir2==temp)
                {
                    fprintf(fpGecici,"\n%d %s %s %f",HesapNumarasi2,ad,soyad,bakiye1);
                }
            }
            fclose(fpGecici);
            fclose(fpHesap);

            //hesaplar klasörü silinir ve yerine yeni deðerlere sahip geçici dosya adý deðiþtirilerek gelir.
            remove("hesaplar.txt");
            rename("gecici.txt","hesaplar.txt");

            printf("\nIslem basarili.");
            printf("\nAna menuye yonlendiriliyorsunuz.");

		}

}

void ParaYatirma()
{

kullanici Hesap;
    float miktar,bakiye;
    int HesapNumarasi,HesapNumarasi1,say=0,satir=0,temp=0,satir2;
    char *ad,*soyad;

     //kullanýcýdan iþlem yapýlacak hesap numarasý alýnýr
    printf("\nHesap numaranizi giriniz:");
    scanf("%d",&HesapNumarasi);

    FILE *fpHesap, *fpGecici;
    //geçici dosya ve hesaplar dosyasý açýlýr
    fpHesap=fopen("hesaplar.txt","r+");
    fpGecici=fopen("gecici.txt","a");

     //dosyanýn sonuna kadar okuma iþlemi gerçekleþtirilmesi için feof kullanýlýr
	while(!feof(fpHesap))
	{
        satir++;
		fscanf(fpHesap,"%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);       //okuma iþlemleri

		if(Hesap.HesapNo==HesapNumarasi)
		{
		    satir2=satir;
            say++;
			printf("\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);       //bilgiler ekrana yazdýrýlýr

            HesapNumarasi1=Hesap.HesapNo;
            bakiye=Hesap.Bakiye;                                /* Hesaba ait deðerler iþlemlerin yapýlmasý için baþka deðiþkenlere atanýr*/
            ad=Hesap.isim;
            soyad=Hesap.Soyad;

            printf("\nHesap dogrulandi.Islem devam ediyor.");

               //kullanýcýdan iþlem yapýlacak miktar alýnýr

            printf("\nLutfen yatirmak istediginiz tutari girin:");
            scanf("%f",&miktar);

            bakiye=bakiye+miktar;
            //yatýrýlan miktar ve son para ekrana yazdýrýlýr
            printf("\n%.2f tl yatirildi yeni bakiye %.2f",miktar,bakiye);
            }
    }
    rewind(fpHesap);
    //eðer hesap numarasý yanlýþsa say deðiþkeni yukarýdaki if bloðuna  girmez ve 0 olarak kalýr
	if(say==0)
    {
        printf("Hesap dogrulanamadi!!!");
    }

    while(!feof(fpHesap))
    {
        temp++;
        fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);    //okuma iþlemleri

        //hesap numarasý yanlýþsa deðerler gecici dosyasýna direk yazdýrýlýr

        if(temp!=satir2)
        {
            fprintf(fpGecici,"\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);

            //hesap numarasý doðruysa iþlem yapýlmýþ yeni deðerler gecici dosyasýna yazdýrýlýr

        }
        else if(temp==satir2)
        {
            fprintf(fpGecici,"\n%d %s %s %f",HesapNumarasi1,ad,soyad,bakiye);
        }

    }
    fclose(fpHesap);
    fclose(fpGecici);

    //geçici dosyasý hesaplar dosyasýyla yer deðiþtirir

    remove("hesaplar.txt");
    rename("gecici.txt","hesaplar.txt");

	}



void HesapOzeti()
{
	kullanici Hesap;
	FILE *fpHesap;
	//hesaplar dosyasý açýlýr
    fpHesap=fopen("hesaplar.txt","r");
    int hesapNumarasi1;
    //kullanýcýdan özetine bakýlacak hesap numarasý alýnýr
    printf("Lutfen hesap ozetini gormek istediginiz hesap numarasini girin:");
    scanf("%d",&hesapNumarasi1);
//dosyanýn sonuna kadar okuma iþlemi gerçekleþtirilmesi için feof kullanýlýr
    while(!feof(fpHesap))
    {
        fscanf(fpHesap,"%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);  //okuma iþlemleri
        if(Hesap.HesapNo==hesapNumarasi1){
        	//hesap numarasý doðruysa deðerler ekrana yazdýrýlýr
        	printf("%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);
		}
	}
}





int main()
{
	setlocale(LC_ALL,"Turkish");
	srand(time(NULL));

	//Menüden istenen iþleme gidilmesi için belirlenmiþ seçim deðiþkeni
	int secim;


	do{

	//Müþteri için görsel menü.
	printf("\n\t**HOÞ GELDÝNÝZ**\n");
	printf("\tYeni Müþteri-->1\n");
	printf("\tHesap açma-->2\n");
	printf("\tPara çekme-->3\n");
	printf("\tPara yatýrma-->4\n");
	printf("\tHesap özeti-->5\n");
	printf("\tÇýkýþ Yapmak için -->9\n");

	//Müþteriden iþlem girdisi alýnýyor.
	printf("Yapmak istediginiz islemi giriniz: ");
	scanf("%d",&secim);

	//Switch case yardýmýyla istenen iþlem için gerekli fonksiyonlara gidiliyor.
            switch(secim)
            {
                case 1:
                    {
                        MusteriEkleme();
                        break;
                    }

                case 2:
                    {
                        HesapAcma();
                        break;

                    }

                case 3:
                    {
                        ParaCekme();
                        break;
                    }

               case 4:
                    {
                        ParaYatirma();
                        break;
                    }
                case 5:
                    {
                        HesapOzeti();
                        break;
                    }
                case 9:
                    {
                        printf("Cikis yapiliyor. Iyi gunler dileriz.");
                        break;
                    }
                default:
                    {
                        printf("Yanlis bir islem girdiniz. Ana menuye donduruluyorsunuz.");
                        break;
                    }


            }
	} while ((secim>=0 && secim<9) || secim>9);
    return 0;
}

