# 高增幅濾波 (in spatial domain)
## 說明
作法與鈍化遮罩一樣，但當權重k>1，就稱為高增幅濾波，但如果k太大，則結果可能不是很好。 
<br>
作法：
1. 產生模糊化影像 (盒狀核與原本影像進行卷積)。  
2. 得到遮罩 (原本影像減去模糊影像)。  
3. 遮罩乘上一個權重比例加回原本影像。  
當k>1時，有高增幅濾波。  

## 結果 (權重k=4.5)
skeleton_orig.bmp：  
![image](https://user-images.githubusercontent.com/86739086/146037560-e19ca50a-d03e-4055-8cd5-bd879fdef99e.png)  
 <br>
blurry_moon.tif：  
![image](https://user-images.githubusercontent.com/86739086/146037576-9af93e94-bddb-4833-95b6-39ce913ab8bf.png)  

