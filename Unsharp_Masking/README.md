# 鈍化遮罩 (in spatial domain)
## 說明
鈍化遮罩的照相處理是基於產生一個模糊的正片，然後它連同原來的負片以產生一個更銳利的影像。  
公式：  
![image](https://user-images.githubusercontent.com/86739086/146036483-8b81b6cf-157a-4931-95bd-36cab823a083.png)  
![image](https://user-images.githubusercontent.com/86739086/146036511-13b1b10d-90dd-4040-a445-0cfb385df02b.png)  
g(x,y)為最後所得到的影像  
h(x,y)為模糊影像  
gmask(x,y)為遮罩  
k為權重  
<br>
作法：
1. 產生模糊化影像 (盒狀核與原本影像進行卷積)。  
2. 得到遮罩 (原本影像減去模糊影像)。  
3. 遮罩乘上一個權重比例加回原本影像。  
當k=1時，會有鈍化遮罩。  

## 結果
skeleton_orig.bmp：  
 ![image](https://user-images.githubusercontent.com/86739086/146036910-ae87279d-4dfe-47e6-a586-9d6452ad23ca.png)  
 <br>
blurry_moon.tif：  
![image](https://user-images.githubusercontent.com/86739086/146036923-ed31f249-7c81-44ce-8169-2c75239fb488.png)  
