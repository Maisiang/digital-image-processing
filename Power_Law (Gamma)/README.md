# 乘冪律
## 說明
用於調整照片的明亮，讓過度曝光的照片暗一點，讓曝光度不足的照片變亮。  
方程式：  
![image](https://user-images.githubusercontent.com/86739086/146012636-f77f41ea-4c36-4102-9cc0-91c3f3e1dd77.png)  
s：轉換後的影像值  
c：正值常數，用於將轉換後的影像調整為0-255間的值。  
r：正值常數，原本的影像值。  
γ(gamma)：改變γ能獲得一組轉換。  


## 結果
Lena.bmp：γ=0.4  
![image](https://user-images.githubusercontent.com/86739086/146003418-3cea070c-73fe-40a7-b4ac-a18ad310d5a7.png)  
Peppers.bmp：γ=3.5  
![image](https://user-images.githubusercontent.com/86739086/146003429-4763c577-586a-4ed2-8263-55143d6b858d.png)  
Cameraman.bmp：γ=0.5  
![image](https://user-images.githubusercontent.com/86739086/146003454-9df1f075-ee25-4cf9-b235-1ac04bec60ae.png)  
