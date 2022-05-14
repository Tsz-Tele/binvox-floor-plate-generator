#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int x,y,f,coverage,cc,cf,planes,i,j,k, px,py,lx,ly,tt;
    char name[100];

    printf("please enter length of x:");
    scanf("%d",&x);
    printf("please enter length of y:");
    scanf("%d",&y);
    printf("please enter the number of floors to be generated:");
    scanf("%d",&f);

    int max;
    max=x;
    if(y>max){
        max=y;
    }
    if(f>max){
        max=f;
    }

    int result[max][max][f];
    printf("please enter the maximum floor coverage to the site: xx%%");
    scanf("%d",&coverage);
    printf("please enter the filename of the floors output:");
    scanf("%s", name);
    srand( time(NULL) );



    for(i=0;i<max;i++){
        for(j=0;j<max;j++){
            for(k=0;k<f;k++){
                result[i][j][k]=0;
            }
        }
    }
    for(cf=0;cf<f;cf++){
        planes=rand()%(x/2 - x/4 + 1) + x/4;
        tt=(x*y*((double)coverage/100));

        for(k=0;k<planes;k++){

                px=rand()%(x - 0 + 1) + 0;
                py=rand()%(y - 0 + 1) + 0;
                lx=rand()%(x/2 - 5 + 1) + 5;
                ly=rand()%(y/2 - 5 + 1) + 5;

                for(i=0;i<lx;i++){
                        for(j=0;j<ly;j++){
                            while(px+i<x&&py+j<y&&tt>0&&result[px+i][py+j][cf]!=1){
                                result[px+i][py+j][cf]=1;
                                tt--;
                            }

                        }
                }


        }

    }



    for(k=0;k<f;k++){
        for(j=0;j<y;j++){
            for(i=0;i<x;i++){
                printf("%d",result[i][j][k]);
            }
            printf("\n");
        }
        printf("\n\n\n");
    }

    FILE *fp;
    fp = fopen( strcat(name , ".binvox"),"wb");

    fprintf(fp, "%s", "#binvox 1\n");

    fprintf(fp, "dim %d %d %d\n", max, max, max );
    fprintf(fp, "%s", "translate 0.0 0.0 0.0\n");
    fprintf(fp, "%s", "scale 1.0\n");
    fprintf(fp, "%s", "data\n");



    for(k=0;k<f;k++){
        for(i=0;i<max;i++){
            for(j=0;j<max;j++){

                    if(result[i][j][k]==1){
                        fprintf(fp,"%c", 0x01);
                        fprintf(fp,"%c", 0x01);



                    }else{
                        fprintf(fp,"%c", 0x00);
                        fprintf(fp,"%c", 0x01);


                    }




            }
        }


    }


    fclose(fp);






}
