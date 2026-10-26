#include <stdio.h>
#include <string.h>

#define MAX_NHAN_VIEN 100
#define TIEN_PHAT 50000

typedef struct {
    int maNV;
    char hoTen[50];
    float luongCoBan;
    int phutMuon;
    float soGioOT;
} NhanVien;

void hienThiMenu(void);
int timKiemTheoMa(NhanVien ds[], int soLuong, int maNV);
void hienThiDanhSach(NhanVien ds[], int soLuong);
int themNhanVien(NhanVien ds[], int soLuong);
void suaNhanVien(NhanVien ds[], int soLuong);
int xoaNhanVien(NhanVien ds[], int soLuong);
void xoaBoDem(void);
int nhapSoNguyen(const char thongBao[]);
float nhapSoThuc(const char thongBao[]);
void nhapHoTen(char hoTen[]);

int main(void) {
    NhanVien ds[MAX_NHAN_VIEN];
    int soLuong = 0;
    int luaChon;

    do {
        hienThiMenu();
        luaChon = nhapSoNguyen("Nhap lua chon: ");

        switch (luaChon) {
            case 1:
                hienThiDanhSach(ds, soLuong);
                break;

            case 2:
                soLuong = themNhanVien(ds, soLuong);
                break;

            case 3:
                suaNhanVien(ds, soLuong);
                break;

            case 4:
                soLuong = xoaNhanVien(ds, soLuong);
                break;

            case 0:
                printf("Da thoat chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (luaChon != 0);

    return 0;
}

void hienThiMenu(void) {
    printf("\n===== HE THONG QUAN LY NHAN SU HRM =====\n");
    printf("1. Xem danh sach nhan vien & Bang luong\n");
    printf("2. Them nhan vien moi\n");
    printf("3. Cap nhat thong tin nhan vien\n");
    printf("4. Xoa nhan vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("=======================================\n");
}

void xoaBoDem(void) {
    int kyTu;

    while ((kyTu = getchar()) != '\n' && kyTu != EOF) {
    }
}

int nhapSoNguyen(const char thongBao[]) {
    int giaTri;
    int ketQua;

    while (1) {
        printf("%s", thongBao);
        ketQua = scanf("%d", &giaTri);

        if (ketQua == 1) {
            xoaBoDem();
            return giaTri;
        }

        printf("Du lieu khong hop le! Hay nhap so nguyen.\n");
        xoaBoDem();
    }
}

float nhapSoThuc(const char thongBao[]) {
    float giaTri;
    int ketQua;

    while (1) {
        printf("%s", thongBao);
        ketQua = scanf("%f", &giaTri);

        if (ketQua == 1) {
            xoaBoDem();
            return giaTri;
        }

        printf("Du lieu khong hop le! Hay nhap so.\n");
        xoaBoDem();
    }
}

void nhapHoTen(char hoTen[]) {
    while (1) {
        printf("Ho ten: ");

        if (fgets(hoTen, 50, stdin) == NULL) {
            hoTen[0] = '\0';
            return;
        }

        if (strchr(hoTen, '\n') != NULL) {
            hoTen[strcspn(hoTen, "\n")] = '\0';
        } else {
            xoaBoDem();
        }

        if (strlen(hoTen) > 0) {
            return;
        }

        printf("Ho ten khong duoc de trong!\n");
    }
}

int timKiemTheoMa(NhanVien ds[], int soLuong, int maNV) {
    int i;

    for (i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }

    return -1;
}

void hienThiDanhSach(NhanVien ds[], int soLuong) {
    int i;
    int tienPhat;
    float tienOT;
    float luongThucNhan;

    if (soLuong == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");

    for (i = 0; i < soLuong; i++) {
        if (ds[i].phutMuon > 15) {
            tienPhat = TIEN_PHAT;
        } else {
            tienPhat = 0;
        }

        tienOT = ds[i].soGioOT
                 * (ds[i].luongCoBan / 160.0)
                 * 1.5;

        luongThucNhan = ds[i].luongCoBan + tienOT - tienPhat;

        printf("\nMa NV: %d\n", ds[i].maNV);
        printf("Ho ten: %s\n", ds[i].hoTen);
        printf("Luong co ban: %.0f\n", ds[i].luongCoBan);
        printf("Phut muon: %d\n", ds[i].phutMuon);
        printf("Gio OT: %.2f\n", ds[i].soGioOT);
        printf("Tien phat: %d\n", tienPhat);
        printf("Tien OT: %.0f\n", tienOT);
        printf("Luong thuc nhan: %.0f\n", luongThucNhan);
    }

    printf("\nTong so nhan vien: %d\n", soLuong);
}

int themNhanVien(NhanVien ds[], int soLuong) {
    NhanVien nv;
    int viTri;

    if (soLuong >= MAX_NHAN_VIEN) {
        printf("Loi: Danh sach da day!\n");
        return soLuong;
    }

    printf("\n--- THEM NHAN VIEN ---\n");

    while (1) {
        nv.maNV = nhapSoNguyen("Ma NV: ");

        if (nv.maNV <= 0) {
            printf("Ma nhan vien phai la so nguyen duong!\n");
        } else {
            viTri = timKiemTheoMa(ds, soLuong, nv.maNV);

            if (viTri != -1) {
                printf("Loi: Ma nhan vien da ton tai!\n");
            } else {
                break;
            }
        }
    }

    nhapHoTen(nv.hoTen);

    while (1) {
        nv.luongCoBan = nhapSoThuc("Luong co ban: ");

        if (nv.luongCoBan < 0) {
            printf("Luong co ban khong duoc am!\n");
        } else {
            break;
        }
    }

    while (1) {
        nv.phutMuon = nhapSoNguyen("Phut di muon: ");

        if (nv.phutMuon < 0) {
            printf("So phut di muon khong duoc am!\n");
        } else {
            break;
        }
    }

    while (1) {
        nv.soGioOT = nhapSoThuc("So gio OT: ");

        if (nv.soGioOT < 0) {
            printf("So gio OT khong duoc am!\n");
        } else {
            break;
        }
    }

    ds[soLuong] = nv;
    soLuong++;

    printf("\n=> Them nhan vien thanh cong!\n");

    return soLuong;
}

void suaNhanVien(NhanVien ds[], int soLuong) {
    int maNV;
    int viTri;
    float luongMoi;
    int phutMuonMoi;
    float gioOTMoi;

    if (soLuong == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return;
    }

    printf("\n--- CAP NHAT THONG TIN NHAN VIEN ---\n");
    maNV = nhapSoNguyen("Nhap ma NV can sua: ");

    viTri = timKiemTheoMa(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("Khong tim thay nhan vien!\n");
        return;
    }

    printf("Nhan vien: %s\n", ds[viTri].hoTen);

    while (1) {
        luongMoi = nhapSoThuc("Nhap luong co ban moi: ");

        if (luongMoi < 0) {
            printf("Luong khong duoc am!\n");
        } else {
            break;
        }
    }

    while (1) {
        phutMuonMoi = nhapSoNguyen("Nhap so phut di muon moi: ");

        if (phutMuonMoi < 0) {
            printf("So phut di muon khong duoc am!\n");
        } else {
            break;
        }
    }

    while (1) {
        gioOTMoi = nhapSoThuc("Nhap so gio OT moi: ");

        if (gioOTMoi < 0) {
            printf("So gio OT khong duoc am!\n");
        } else {
            break;
        }
    }

    ds[viTri].luongCoBan = luongMoi;
    ds[viTri].phutMuon = phutMuonMoi;
    ds[viTri].soGioOT = gioOTMoi;

    printf("=> Cap nhat nhan vien thanh cong!\n");
}

int xoaNhanVien(NhanVien ds[], int soLuong) {
    int maNV;
    int viTri;
    int i;

    if (soLuong == 0) {
        printf("\nDanh sach nhan vien dang rong!\n");
        return soLuong;
    }

    printf("\n--- XOA NHAN VIEN ---\n");
    maNV = nhapSoNguyen("Ma NV can xoa: ");

    viTri = timKiemTheoMa(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("Khong tim thay nhan vien!\n");
        return soLuong;
    }

    for (i = viTri; i < soLuong - 1; i++) {
        ds[i] = ds[i + 1];
    }

    soLuong--;

    printf("=> Xoa nhan vien thanh cong!\n");

    return soLuong;
}
