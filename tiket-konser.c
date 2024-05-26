#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct node {
    char nama[100];
    int noKursi;
    char kategoriKursi[100];
    struct node* next;
} node;

int queue[MAX_SIZE];
int front = -1;
int rear = -1;
int showQueueMenu = 1;
node* head = NULL;
node* tail = NULL;

void enqueue() {
    if (rear == MAX_SIZE - 1) {
        printf("\nAntrian penuh.\n\n");
    } else {
        int number = rear + 2;
        queue[++rear] = number;
        printf("\nPenambahan Antrian Berhasil\n\n");
    }
    system("pause");
}

int dequeue() 
{
    if (front == rear) {
        printf("\nAntrian Kosong.\n\n");
        system("pause");
        return 0;
    } else {
        int number = queue[++front];
        printf("\nAntrian keluar\n");
        printf("\nTekan tombol apa saja untuk melanjutkan ke Loket Tiket\n\n");
            if (front < rear) {
                queue[front + 1] = 1;
            }
        system("pause");
        return 1; 
    }
}

void showQueue() 
{
    int count = rear - front;
    printf("\nTotal orang di antrian: %d.\n\n", count);
    system("pause");
}

void tampilkanKursi(int baris, int kolom, char kategoriKursi[], int maksKursi) {
    system("cls");
    printf("PENGATURAN TEMPAT KURSI (%s)\n", kategoriKursi);
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            int kursi = (i * kolom) + (j + 1);
            int booked = 0;  // Flag untuk menandai kursi yang sudah dibooking
            node* current = head;
            while (current != NULL) {
                if (strcmp(current->kategoriKursi, kategoriKursi) == 0 && current->noKursi == kursi) {
                    booked = 1;  // Kursi sudah dibooking
                    break;
                }
                current = current->next;
            }
            if (booked) {
                printf("  X ");
            } else {
                printf("%3d ", kursi);
            }
        }
        printf("\n");
    }
}

void addList(char nama[], char kategoriKursi[], int noKursi) {
    node* newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->nama, nama);
    newNode->noKursi = noKursi;
    strcpy(newNode->kategoriKursi, kategoriKursi);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    printf("\nData Tiket Berhasil Disimpan\n\n");
    system("pause");
}

void cariTiket() {
    char nama[100];
    printf("Masukkan nama yang ingin dicari: ");
    scanf(" %[^\n]", nama);

    char kategoriKursi[100];
    printf("Masukkan kategori kursi: ");
    scanf(" %[^\n]", kategoriKursi);

    int noKursi;
    printf("Masukkan nomor kursi: ");
    scanf("%d", &noKursi);

    node* current = head;
    node* prev = NULL;
    int found = 0;
    int count = 0;

    while (current != NULL) {
        if (strcmp(current->nama, nama) == 0 && strcmp(current->kategoriKursi, kategoriKursi) == 0 && current->noKursi == noKursi) {
            found = 1;
            printf("Tiket ditemukan:\n");
            printf("Nama        : %s\n", current->nama);
            printf("Kategori    : %s\n", current->kategoriKursi);
            printf("Nomor Kursi : %d\n", current->noKursi);

            char x;
            printf("Apakah Anda ingin menghapus tiket ini? [Y/N] : ");
            scanf(" %c", &x);

            if (x == 'Y' || x == 'y') {
                if (current == head) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }

                free(current);
                printf("Tiket berhasil dihapus.\n");
            }
            break;
        }

        prev = current;
        current = current->next;
        count++;
    }

    if (!found) {
        printf("Tiket tidak ditemukan.\n");
        system("pause");
    }
}

void tampilkanTiket() {
    node* current = head;
    int count = 0;

    printf("Data Tiket:\n");
    printf("-----------------------------------------------------\n");
    printf("No.  Nama        Kategori Kursi    No. Kursi\n");
    printf("-----------------------------------------------------\n");

    while (current != NULL) {
        printf("%-5d%-15s%-18s%-10d\n", ++count, current->nama, current->kategoriKursi, current->noKursi);
        current = current->next;
    }

    printf("-----------------------------------------------------\n");
}

void pesanTiket(char kategoriKursi[], int maksKursi) {
    char x;
    printf("Lanjutkan Pesanan [Y/N] : ");
    scanf(" %c", &x);
    if (x == 'Y' || x == 'y') {
        char nama[100], email[100];
        int noKursi;
        printf("\nMasukkan nama : ");
        scanf(" %[^\n]", nama);

        node* current = head;

        while (1) {
            printf("Pilih nomor kursi : ");
            scanf("%d", &noKursi);
            if (noKursi >= 1 && noKursi <= maksKursi) {
                // Periksa apakah kursi sudah dibooking
                current = head;
                while (current != NULL) {
                    if (strcmp(current->kategoriKursi, kategoriKursi) == 0 && current->noKursi == noKursi) {
                        printf("Kursi sudah dibooking. Silakan pilih kursi lain.\n");
                        return;
                    }
                    current = current->next;
                }
                break;
            } else {
                printf("Nomor kursi tidak valid. Harap masukkan nomor kursi antara 1 dan %d.\n", maksKursi);
            }
        }
        addList(nama, kategoriKursi, noKursi);
    }
}

void kategoriTiket() {
    int choice = 0;
    while (1) {
        system("cls");
        printf("\n\t KATEGORI TIKET\n"
                "\n\t 1. VIP\n"
                "\n\t 2. CAT 1\n"
                "\n\t 3. CAT 2\n"
                "\n\t 4. Keluar\n"
                "\nMasukkan Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                tampilkanKursi(3, 10, "VIP", 30);
                pesanTiket("VIP", 30);
                break;
            case 2:
                tampilkanKursi(4, 10, "CAT1", 40);
                pesanTiket("CAT1", 40);
                break;
            case 3:
                tampilkanKursi(4, 10, "CAT2", 40);
                pesanTiket("CAT2", 40);
                break;
            case 4: 
                return;
            default:
                printf("\nPilihan tidak valid.\n\n");
                system("pause");
        }
    }
}

void loketTiket() {
    int choice = 0;
    while (1) {
        system("cls");
        printf("\n\t LOKET TIKET \n"
                "\n\t 1. Beli Tiket\n"
                "\n\t 2. Daftar Tiket\n"
                "\n\t 3. Cari / Hapus Tiket\n"
                "\n\t 4. Keluar\n"
                "\nMasukkan Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                kategoriTiket();
                break;
            case 2:
                system("cls");
                tampilkanTiket();
                system("pause");
                break;
            case 3:
                system("cls");
                cariTiket();
                break;
            case 4:
                return;
            default:
                printf("\nPilihan tidak valid.\n\n");
                system("pause");
        }
    }
}


int main() 
{
    int choice = 0;
    while (1) {
        system("cls");
        printf("\n\t ANTRIAN \n"
                "\n\t 1. Masuk Antrian\n"
                "\n\t 2. Keluar Antrian\n"
                "\n\t 3. Lihat Antrian\n"
                "\n\t 4. Keluar\n"
                "\n Masukan Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue();
                system("cls");
                break;
            case 2:
                if (dequeue())
                    loketTiket();
                break;
            case 3:
                showQueue();
                system("cls");
                break;
            case 4:
                printf("\nProgram Berhenti.\n\n");
                return 0;
                break;
            default:
                printf("\nPilihan tidak valid.\n\n");
                system("pause");
        }
    }
}
