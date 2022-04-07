#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>                                                    //25. grup banka otomasyonu
#include <locale.h>
                                                                     /* ismail acar 201180037 */
                                                                     /* ay�enur yava�o�lu 201180024 */
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

		//M��teri bilgilerinin istenece�ine dair bilgilendiriliyor.
		printf("Bankam�za ho� geldiniz.L�tfen bilgilerinizi giriniz.\n");

		//M��teriden ad� al�n�yor.
		printf("Ad:");
		scanf("%s",musteri.isim);

		//M��teriden soyad� al�n�yor.
		printf("Soyad:");
		scanf("%s",musteri.Soyad);

		//M��teriden do�um yeri bilgisi al�n�yor.
		printf("Dogum yeri:");
		scanf("%s",musteri.dyeri);

		//M��teriden tc kimlik no bilgisi al�n�yor.
		printf("TC:");
		scanf("%s",musteri.tc);

		//M��teriye sistem taraf�ndan rastgele m��teri numaras� atan�yor ve m��teriye bildiriliyor.
		printf("Musteri numarasi:");
		musteri.MusteriNo=rand()%100+100;
		printf("%d",musteri.MusteriNo);

		//Dosya i�lemleri i�in musteriler.txt dosyas� a��l�yor (�st�ne yazma modunda).
		fpmusteri=fopen("musteriler.txt","a");


		//fprintf fonksiyonu ile m��teriden ald���m�z bilgiler istedi�imiz �ekilde dosyaya yaz�l�yor.
		fprintf(fpmusteri,"\n%d %s %s %s %s",musteri.MusteriNo,musteri.isim,musteri.Soyad,musteri.dyeri,musteri.tc);

		//Dosya kapan�yor.
		fclose(fpmusteri);

	}



void HesapAcma()
{
    kullanici Hesap;
    kullanici musteri;
    int musteriNo,secim;
    FILE *fpHesap,*fp1;

    //Hesaplar dosyas�n� �st�ne yazma moduyla a��yoruz.
    fpHesap=fopen("hesaplar.txt","a");

	//M��teri karar�n� de�i�tirmi�se men�ye d�nebilmesi i�in bir se�enek sunuluyor.
    printf("\nDevam etmek i�in->1 e bas�n�z men�ye d�nmek i�in ->2\n");
    scanf("%d",&secim);

	//M��terinin se�imine g�re karar mekanizmalar� �al���yor.
    if(secim==1)
    {
        int say=0;

        //musteriler.txt dosyas� okuma modunda a��l�yor.
        fp1=fopen("musteriler.txt","r");

        //M��teriden kendisine sistem taraf�ndan atanm�� olan m��teri numaras� isteniyor.
        printf("Lutfen musteri no girin:");
        scanf("%d",&musteriNo);

        //Okuma modunda a�t���m�z dosyadaki kay�tl� bilgileri al�yoruz.
	    while(!feof(fp1))
	    {
	        fscanf(fp1,"\n%d %s %s %s %s ",&musteri.MusteriNo,&musteri.isim,&musteri.Soyad,&musteri.dyeri,&musteri.tc);

	        //E�er m��terinin girdi�i m��teri no dosyadan okudu�umuz m��teri no ile uyu�uyorsa �al���yor.
		    if(musteri.MusteriNo==musteriNo)
            {

            	//M��teriye hesap bilgileri g�steriliyor.
                printf("\n%d %s %s %s %s ",musteri.MusteriNo,musteri.isim,musteri.Soyad,musteri.dyeri,musteri.tc);
		        ++say;

				//M��teri bilgilendirmesi.
                printf("\nHesabiniz dogrulandi.Hesap acma islemi devam ediyor.");

				//M��teriye sistem taraf�ndan rastgele bir hesap numaras� veriliyor.
                Hesap.HesapNo=rand()%100+100;
                printf("\nHesap numaraniz: %d",Hesap.HesapNo);

                //M��teriden ilk bakiyesi isteniyor (0'dan ba�latmak yerine m��teri istedi�i bakiyeyle hesab�n� a�abiliyor.).
                printf("\nIlk bakiyenizi giriniz:");
                scanf("%f",&Hesap.Bakiye);

				//M��teri bilgilendirmesi.
                printf("\nIslem tamamlandi.Iyi gunler dileriz.");

				//M��teriden ald���m�z bilgileri hesaplar dosyas�na istedi�imiz �ekilde kaydediyoruz.
                fprintf(fpHesap,"\n%d %s %s %.2f",Hesap.HesapNo,musteri.isim,musteri.Soyad,Hesap.Bakiye);

            }
	    }

	    //Dosyalarla i�imiz bitti�inden onlar� kapat�yoruz.
		fclose(fp1);
		fclose(fpHesap);

		/*Fonksiyonun ba��nda 0 olarak atad���m�z say de�i�kenimiz e�er yukar�daki if blo�una girseydi say++ komutuyla 1 artacakt� ve 0 olmayacakt� dolay�s�yla bu kod �al��mayacakt�.
		Yani yukar�daki if blo�una giren durumlar (ki bu durumlar do�rulanman�n sa�land��� durumlard�r) say de�i�kenimizi art�rarak 0 olmaktan kurtar�yor.
		B�ylece alttaki if blo�una girmeyecek. Fakat e�er ki �stteki if blo�una girilmemi�se yani m��teriden al�nan m��teri no ile dosyadaki m��teri no tutmuyor ise
		o zaman say++ komutu �al��mam�� olacak ve say=0 olarak kald���ndan bu blo�a girilecek.*/
	    if(say==0)
	    {
	    	//M��teri bilgilendirmesi
	    	printf("\nHesap dogrulanamadi!!!");

		}


	}
}

void ParaCekme()
{
	 kullanici Hesap;
     // de�i�kenlerin atand��� k�s�m
    float miktar,bakiye1;
    int HesapNumarasi,HesapNumarasi2,say1=0;
	int satir=0,satir2,temp=0;
	char *ad,*soyad;

        // hesap dosyas�n�n ve i�lemlerin �zerine yaz�l�p hesap dosyas�n�n yerine ge�ecek ge�ici dosyan�n pointerlar� atan�yor
        FILE *fpHesap,*fpGecici;

        fpHesap=fopen("hesaplar.txt","r");
		//kullan�c�dan i�lem yap�lacak hesap numaras� isteniyor
        printf("\nLutfen hesap numarasi girin:");
        scanf("%d",&HesapNumarasi);

        //dosyan�n sonuna kadar okuma i�lemi ger�ekle�tirilmesi i�in feof kullan�l�r
        while(!feof(fpHesap))
	    {
	        satir++;
		    fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);   //okuma i�lemleri

	    	if(Hesap.HesapNo==HesapNumarasi)
	    	{
		        say1++;
                satir2=satir;
                HesapNumarasi2=Hesap.HesapNo;
		        bakiye1=Hesap.Bakiye;                                       /* Hesaba ait de�erler i�lemlerin yap�lmas� i�in ba�ka de�i�kenlere atan�r*/
		        ad=Hesap.isim;
		        soyad=Hesap.Soyad;
		    	printf("\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,bakiye1);         //ekrana kullan�c�n�n bilgileri yazd�r�l�r/
		    	printf("\nHesap numarasi dogrulandi.Isleminiz devam ediyor.");
            }
        }
		fclose(fpHesap);
		// e�er girilen  hesap numaras� bulunmuyorsa say1 de�i�keni �stteki if blo�una girmedi�i i�in 0 kal�r b�ylece hesap numaras�n�n do�rulu�u kontrol edilmi� olur.
        if(say1==0)
        {
            printf("Hesap dogrulanamadi!!!");
            printf("\nCikis yapiliyor.");
            exit(0);

        }
         //m��teriden �ekilecek tutar al�n�r
	    printf("\nCekmek istediginiz tutari giriniz:");
        scanf("%f",&miktar);
		// �ekilecek miktar bakiyeden daha fazla olursa i�lem ger�ekle�mez
        if(miktar>bakiye1)
		{
            printf("Bakiyeniz yetersizdir.");

		}
       //miktar k���kse hesaptan para �ekme i�lemi ger�ekle�ir
        if(miktar<=bakiye1)
        {
            bakiye1=bakiye1-miktar;
            //�ekilen miktar ve kalan para ekrana yazd�r�l�r
            printf("\n%.2f TL para cekildi.Kalan bakiye:%.2f",miktar,bakiye1);
            fpHesap=fopen("hesaplar.txt","r");
            //ge�ici bir dosya a��l�r
            fpGecici=fopen("gecici.txt","a");

            while(!feof(fpHesap))
            {
                temp++;
                fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);

                //e�er hesap numaras� do�ru de�ilse i�leme girmez yani de�erleri ba�ka de�i�kene atanmaz ve oldu�u gibi gecici dosyas�na yazd�r�l�r
              if(satir2!=temp)
                {
                    fprintf(fpGecici,"\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);
                }

                //e�er hesap numaras� do�ruysa i�leme girer ve yeni de�erler �zerinde i�lem yap�lan de�i�kenler vas�tas�yla gecici dosyas�na yazd�r�l�r.

                if(satir2==temp)
                {
                    fprintf(fpGecici,"\n%d %s %s %f",HesapNumarasi2,ad,soyad,bakiye1);
                }
            }
            fclose(fpGecici);
            fclose(fpHesap);

            //hesaplar klas�r� silinir ve yerine yeni de�erlere sahip ge�ici dosya ad� de�i�tirilerek gelir.
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

     //kullan�c�dan i�lem yap�lacak hesap numaras� al�n�r
    printf("\nHesap numaranizi giriniz:");
    scanf("%d",&HesapNumarasi);

    FILE *fpHesap, *fpGecici;
    //ge�ici dosya ve hesaplar dosyas� a��l�r
    fpHesap=fopen("hesaplar.txt","r+");
    fpGecici=fopen("gecici.txt","a");

     //dosyan�n sonuna kadar okuma i�lemi ger�ekle�tirilmesi i�in feof kullan�l�r
	while(!feof(fpHesap))
	{
        satir++;
		fscanf(fpHesap,"%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);       //okuma i�lemleri

		if(Hesap.HesapNo==HesapNumarasi)
		{
		    satir2=satir;
            say++;
			printf("\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);       //bilgiler ekrana yazd�r�l�r

            HesapNumarasi1=Hesap.HesapNo;
            bakiye=Hesap.Bakiye;                                /* Hesaba ait de�erler i�lemlerin yap�lmas� i�in ba�ka de�i�kenlere atan�r*/
            ad=Hesap.isim;
            soyad=Hesap.Soyad;

            printf("\nHesap dogrulandi.Islem devam ediyor.");

               //kullan�c�dan i�lem yap�lacak miktar al�n�r

            printf("\nLutfen yatirmak istediginiz tutari girin:");
            scanf("%f",&miktar);

            bakiye=bakiye+miktar;
            //yat�r�lan miktar ve son para ekrana yazd�r�l�r
            printf("\n%.2f tl yatirildi yeni bakiye %.2f",miktar,bakiye);
            }
    }
    rewind(fpHesap);
    //e�er hesap numaras� yanl��sa say de�i�keni yukar�daki if blo�una  girmez ve 0 olarak kal�r
	if(say==0)
    {
        printf("Hesap dogrulanamadi!!!");
    }

    while(!feof(fpHesap))
    {
        temp++;
        fscanf(fpHesap,"\n%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);    //okuma i�lemleri

        //hesap numaras� yanl��sa de�erler gecici dosyas�na direk yazd�r�l�r

        if(temp!=satir2)
        {
            fprintf(fpGecici,"\n%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);

            //hesap numaras� do�ruysa i�lem yap�lm�� yeni de�erler gecici dosyas�na yazd�r�l�r

        }
        else if(temp==satir2)
        {
            fprintf(fpGecici,"\n%d %s %s %f",HesapNumarasi1,ad,soyad,bakiye);
        }

    }
    fclose(fpHesap);
    fclose(fpGecici);

    //ge�ici dosyas� hesaplar dosyas�yla yer de�i�tirir

    remove("hesaplar.txt");
    rename("gecici.txt","hesaplar.txt");

	}



void HesapOzeti()
{
	kullanici Hesap;
	FILE *fpHesap;
	//hesaplar dosyas� a��l�r
    fpHesap=fopen("hesaplar.txt","r");
    int hesapNumarasi1;
    //kullan�c�dan �zetine bak�lacak hesap numaras� al�n�r
    printf("Lutfen hesap ozetini gormek istediginiz hesap numarasini girin:");
    scanf("%d",&hesapNumarasi1);
//dosyan�n sonuna kadar okuma i�lemi ger�ekle�tirilmesi i�in feof kullan�l�r
    while(!feof(fpHesap))
    {
        fscanf(fpHesap,"%d %s %s %f",&Hesap.HesapNo,Hesap.isim,Hesap.Soyad,&Hesap.Bakiye);  //okuma i�lemleri
        if(Hesap.HesapNo==hesapNumarasi1){
        	//hesap numaras� do�ruysa de�erler ekrana yazd�r�l�r
        	printf("%d %s %s %f",Hesap.HesapNo,Hesap.isim,Hesap.Soyad,Hesap.Bakiye);
		}
	}
}





int main()
{
	setlocale(LC_ALL,"Turkish");
	srand(time(NULL));

	//Men�den istenen i�leme gidilmesi i�in belirlenmi� se�im de�i�keni
	int secim;


	do{

	//M��teri i�in g�rsel men�.
	printf("\n\t**HO� GELD�N�Z**\n");
	printf("\tYeni M��teri-->1\n");
	printf("\tHesap a�ma-->2\n");
	printf("\tPara �ekme-->3\n");
	printf("\tPara yat�rma-->4\n");
	printf("\tHesap �zeti-->5\n");
	printf("\t��k�� Yapmak i�in -->9\n");

	//M��teriden i�lem girdisi al�n�yor.
	printf("Yapmak istediginiz islemi giriniz: ");
	scanf("%d",&secim);

	//Switch case yard�m�yla istenen i�lem i�in gerekli fonksiyonlara gidiliyor.
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

