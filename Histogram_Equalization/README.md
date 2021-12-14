# Global版本 直方圖等化
## 變數
MN    ：影像總共像素，假設圖片大小為256x256，MN為65536。  
L     ：圖片為n位元影像，這邊設定為256，因為圖片為 8 位元的影像。  
n[256]：存放 0-255 各階的像素數量。  
p[256]：存放在每階在圖中出現的次數。  
s[256]：存放等化後的值，四捨五入後放到 Result 陣列裡面。  

## 作法
1. n陣列初始化，使用uchar指標讀取型態為Mat的src開頭，利用迴圈去計算全部像素各階的像素數量。  
2. 計算每一階出現的機率存到p陣列。  
3. 利用p陣列算出等化結果放到s陣列。  
4. 四捨五入，並得到直方圖等化的影像。  

## 結果
1. Lena.bmp：  
![image](https://user-images.githubusercontent.com/86739086/146002181-be2f97d9-20cf-440a-bce4-bc5dfeaba5fa.png =50%x)
2. Peppers.bmp：  
![image](https://user-images.githubusercontent.com/86739086/146002199-d9e41e2d-2657-4162-b98f-2acd6428082d.png =50%x)
3. Cameraman.bmp：  
![image](https://user-images.githubusercontent.com/86739086/146002209-f19e4bfd-2242-48b8-9957-3ba34dd65467.png =50%x)

