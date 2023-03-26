#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>                                                    
#include <locale.h>
                                                                     
                                                                   
typedef struct{                                                      
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

		//Müşteri bilgilerinin isteneceğine dair bilgilendiriliyor.
		printf("Bankamıza hoş geldiniz.Lütfen bilgilerinizi giriniz.\n");

		//Müşteriden adı alınıyor.
		printf("Ad:");
		scanf("%s",musteri.isim);

		//Müşteriden soyadı alınıyor.
		printf("Soyad:");
		scanf("%s",musteri.Soyad);

		//Müşteriden doğum yeri bilgisi alınıyor.
		printf("Dogum yeri:");
		scanf("%s",musteri.dyeri);

		//Müşteriden tc kimlik no bilgisi alınıyor.
		printf("TC:");
		scanf("%s",musteri.tc);

		//Müşteriye sistem tarafından rastgele müşteri numarası atanıyor ve müşteriye bildiriliyor.
		printf("Musteri numarasi:");
		musteri.MusteriNo=rand()%100+100;
		printf("%d",musteri.MusteriNo);

		//Dosya işlemleri için musteriler.txt dosyası açılıyor (Üstüne yazma modunda).
		fpmusteri=fopen("musteriler.txt","a");


		//fprintf fonksiyonu ile müşteriden aldığımız bilgiler istediğimiz şekilde dosyaya yazılıyor.
		fprintf(fpmusteri,"\n%d %s %s %s %s",musteri.MusteriNo,musteri.isim,musteri.Soyad,musteri.dyeri,musteri.tc);

		//Dosya kapanıyor.
		fclose(fpmusteri);

	}



void HesapAcma()
{
    kullanici Hesap;
    kullanici musteri;
    int musteriNo,secim;
    FILE *fpHesap,*fp1;

    //Hesaplar dosyasını üstüne yazma moduyla açıyoruz.
    fpHesap=fopen("hesaplar.txt","a");

	//Müşteri kararını değiştirmişse menüye dönebilmesi için bir seçenek sunuluyor.
    printf("\nDevam etmek için->1 e basınız menüye dönmek için ->2\n");
    scanf("%d",&secim);

	//Müşterinin seçimine göre karar mekanizmaları çalışıyor.
    if(secim==1)
    {
        int say=0;

        //musteriler.txt dosyası okuma modunda açılıyor.
        fp1=fopen("musteriler.txt","r");

        //Müşteriden kendisine sistem tarafından atanmış olan müşteri numarası isteniyor.
        printf("Lutfen musteri no girin:");
        scanf("%d",&musteriNo);

        //Okuma modunda açtığımız dosyadaki kayıtlı bilgileri alıyoruz.
	    while(!feof(fp1))
	    {
	        fscanf(fp1,"\n%d %s %s %s %s ",&musteri.MusteriNo,&musteri.isim,&musteri.Soyad,&musteri.dyeri,&musteri.tc);

	        //Eğer müşterinin girdiği müşteri no dosyadan okuduğumuz müşteri no ile uyuşuyorsa çalışıyor.
		    if(musteri.MusteriNo==musteriNo)
            {

            	//Müşteriye hesap bilgileri gösteriliyor.
                printf("\n%d %s %s %s %s ",musteri.MusteriNo,musteri.isim,musteri.Soyad,musteri.dyeri,musteri.tc);
		        ++say;

				//Müşteri bilgilendirmesi.
                printf("\nHesabiniz dogrulandi.Hesap acma islemi devam ediyor.");

				//Müşteriye sistem tarafından rastgele bir hesap numarası veriliyor.
                Hesap.HesapNo=rand()%100+100;
                printf("\nHesap numaraniz: %d",Hesap.HesapNo);

                //Müşteriden ilk bakiyesi isteniyor (0'dan başlatmak yerine müşteri istediği bakiyeyle hesabını açabiliyor.).
                printf("\nIlk bakiyenizi giriniz:");
                scanf("%f",&Hesap.Bakiye);

				//Müşteri bilgilendirmesi.
                printf("\nIslem tamamlandi.Iyi gunler dileriz.");

				//Müşteriden aldığımız bilgileri hesaplar dosyasına istediğimiz şekilde kaydediyoruz.
                fprintf(fpHesap,"\n%d %s %s %.2f",Hesap.HesapNo,musteri.isim,musteri.Soyad,Hesap.Bakiye);

            }
	    }

	    //Dosyalarla işimiz bittiğinden onları kapatıyoruz.
		fclose(fp1);
		fclose(fpHesap);

		/*Fonksiyonun başında 0 olarak atadığımız say değişkenimiz eğer yukarıdaki if bloğuna girseydi say++ komutuyla 1 artacaktı ve 0 olmayacaktı dolayısıyla bu kod çalışmayacaktı.
		Yani yukarıdaki if bloğuna giren durumlar (ki bu durumlar doğrulanmanın sağlandığı durumlardır) say değişkenimizi artırarak 0 olmaktan kurtarıyor.
		Böylece alttaki if bloğuna girmeyecek. Fakat eğer ki üstteki if bloğuna girilmemişse yani müşteriden alınan müşteri no ile dosyadaki müşteri no tutmuyor ise
		o zaman say++ komutu çalışmamış olacak ve say=0 olarak kaldığından bu bloğa girilecek.*/
	    if(say==0)
	    {
	    	//Müşteri bilgilendirmesi
	    	printf("\nHesap dogrulanamadi!!!");

		}


	}
}

void ParaCekme()
{
	 kullanici Hesap;
     // değişkenlerin atandığı kısım
    float miktar,bakiye1;
    int HesapNumarasi,HesapNumarasi2,say1=0;
	int satir=0,satir2,temp=0;
	char *ad,*soyad;

        // hesap dosyasının ve işlemlerin üzerine yazılıp hesap dosyasının yerine geçecek geçici dosyanın pointerları atanıyor
        FILE *fpHesap,*fpGecici;

        fpHesap=fopen("hesaplar.txt","r");
		//kullanıcıdan işlem yapılacak hesap numarası isteniyor
        printf("\nLutfen hesap numarasi girin:");
        scanf("%d",&HesapNumarasi);

        //dosyanın sonuna kadar okuma işlemi gerçekleştirilmesi için feof kullanılır
        while(!feof(fpHesap))
	    {
	        satir++;
		    fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);   //okuma işlemleri

	    	if(Hesap.HesapNo==HesapNumarasi)
	    	{
		        say1++;
                satir2=satir;
                HesapNumarasi2=Hesap.HesapNo;
		        bakiye1=Hesap.Bakiye;                                       /* Hesaba ait değerler işlemlerin yapılması için başka değişkenlere atanır*/
		        ad=Hesap.isim;
		        soyad=Hesap.Soyad;
		    	printf("\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,bakiye1);         //ekrana kullanıcının bilgileri yazdırılır/
		    	printf("\nHesap numarasi dogrulandi.Isleminiz devam ediyor.");
            }
        }
		fclose(fpHesap);
		// eğer girilen  hesap numarası bulunmuyorsa say1 değişkeni üstteki if bloğuna girmediği için 0 kalır böylece hesap numarasının doğruluğu kontrol edilmiş olur.
        if(say1==0)
        {
            printf("Hesap dogrulanamadi!!!");
            printf("\nCikis yapiliyor.");
            exit(0);

        }
         //müşteriden çekilecek tutar alınır
	    printf("\nCekmek istediginiz tutari giriniz:");
        scanf("%f",&miktar);
		// çekilecek miktar bakiyeden daha fazla olursa işlem gerçekleşmez
        if(miktar>bakiye1)
		{
            printf("Bakiyeniz yetersizdir.");

		}
       //miktar küçükse hesaptan para çekme işlemi gerçekleşir
        if(miktar<=bakiye1)
        {
            bakiye1=bakiye1-miktar;
            //çekilen miktar ve kalan para ekrana yazdırılır
            printf("\n%.2f TL para cekildi.Kalan bakiye:%.2f",miktar,bakiye1);
            fpHesap=fopen("hesaplar.txt","r");
            //geçici bir dosya açılır
            fpGecici=fopen("gecici.txt","a");

            while(!feof(fpHesap))
            {
                temp++;
                fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);

                //eğer hesap numarası doğru değilse işleme girmez yani değerleri başka değişkene atanmaz ve olduğu gibi gecici dosyasına yazdırılır
              if(satir2!=temp)
                {
                    fprintf(fpGecici,"\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);
                }

                //eğer hesap numarası doğruysa işleme girer ve yeni değerler üzerinde işlem yapılan değişkenler vasıtasıyla gecici dosyasına yazdırılır.

                if(satir2==temp)
                {
                    fprintf(fpGecici,"\n%d %s %s %f",HesapNumarasi2,ad,soyad,bakiye1);
                }
            }
            fclose(fpGecici);
            fclose(fpHesap);

            //hesaplar klasörü silinir ve yerine yeni değerlere sahip geçici dosya adı değiştirilerek gelir.
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

     //kullanıcıdan işlem yapılacak hesap numarası alınır
    printf("\nHesap numaranizi giriniz:");
    scanf("%d",&HesapNumarasi);

    FILE *fpHesap, *fpGecici;
    //geçici dosya ve hesaplar dosyası açılır
    fpHesap=fopen("hesaplar.txt","r+");
    fpGecici=fopen("gecici.txt","a");

     //dosyanın sonuna kadar okuma işlemi gerçekleştirilmesi için feof kullanılır
	while(!feof(fpHesap))
	{
        satir++;
		fscanf(fpHesap,"%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);       //okuma işlemleri

		if(Hesap.HesapNo==HesapNumarasi)
		{
		    satir2=satir;
            say++;
			printf("\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);       //bilgiler ekrana yazdırılır

            HesapNumarasi1=Hesap.HesapNo;
            bakiye=Hesap.Bakiye;                                /* Hesaba ait değerler işlemlerin yapılması için başka değişkenlere atanır*/
            ad=Hesap.isim;
            soyad=Hesap.Soyad;

            printf("\nHesap dogrulandi.Islem devam ediyor.");

               //kullanıcıdan işlem yapılacak miktar alınır

            printf("\nLutfen yatirmak istediginiz tutari girin:");
            scanf("%f",&miktar);

            bakiye=bakiye+miktar;
            //yatırılan miktar ve son para ekrana yazdırılır
            printf("\n%.2f tl yatirildi yeni bakiye %.2f",miktar,bakiye);
            }
    }
    rewind(fpHesap);
    //eğer hesap numarası yanlışsa say değişkeni yukarıdaki if bloğuna  girmez ve 0 olarak kalır
	if(say==0)
    {
        printf("Hesap dogrulanamadi!!!");
    }

    while(!feof(fpHesap))
    {
        temp++;
        fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);    //okuma işlemleri

        //hesap numarası yanlışsa değerler gecici dosyasına direk yazdırılır

        if(temp!=satir2)
        {
            fprintf(fpGecici,"\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);

            //hesap numarası doğruysa işlem yapılmış yeni değerler gecici dosyasına yazdırılır

        }
        else if(temp==satir2)
        {
            fprintf(fpGecici,"\n%d %s %s %f",HesapNumarasi1,ad,soyad,bakiye);
        }

    }
    fclose(fpHesap);
    fclose(fpGecici);

    //geçici dosyası hesaplar dosyasıyla yer değiştirir

    remove("hesaplar.txt");
    rename("gecici.txt","hesaplar.txt");

	}



void HesapOzeti()
{
	kullanici Hesap;
	FILE *fpHesap;
	//hesaplar dosyası açılır
    fpHesap=fopen("hesaplar.txt","r");
    int hesapNumarasi1;
    //kullanıcıdan özetine bakılacak hesap numarası alınır
    printf("Lutfen hesap ozetini gormek istediginiz hesap numarasini girin:");
    scanf("%d",&hesapNumarasi1);
//dosyanın sonuna kadar okuma işlemi gerçekleştirilmesi için feof kullanılır
    while(!feof(fpHesap))
    {
        fscanf(fpHesap,"%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);  //okuma işlemleri
        if(Hesap.HesapNo==hesapNumarasi1){
        	//hesap numarası doğruysa değerler ekrana yazdırılır
        	printf("%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);
		}
	}
}





int main()
{
	setlocale(LC_ALL,"Turkish");
	srand(time(NULL));

	//Menüden istenen işleme gidilmesi için belirlenmiş seçim değişkeni
	int secim;


	do{

	//Müşteri için görsel menü.
	printf("\n\t**HOŞ GELDİNİZ**\n");
	printf("\tYeni Müşteri-->1\n");
	printf("\tHesap açma-->2\n");
	printf("\tPara çekme-->3\n");
	printf("\tPara yatırma-->4\n");
	printf("\tHesap özeti-->5\n");
	printf("\tÇıkış Yapmak için -->9\n");

	//Müşteriden işlem girdisi alınıyor.
	printf("Yapmak istediginiz islemi giriniz: ");
	scanf("%d",&secim);

	//Switch case yardımıyla istenen işlem için gerekli fonksiyonlara gidiliyor.
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

