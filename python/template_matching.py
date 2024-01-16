import cv2
import serial
import time

def posToDegree(pos):
    return int(45/1000*pos + 30)

def main():
    # テンプレート画像の読み込み
    template = cv2.imread('template.jpg', cv2.IMREAD_COLOR)
    
    # Webカメラを起動
    cap = cv2.VideoCapture(0)
    
    # フレームレートを設定（10fps）
    cap.set(cv2.CAP_PROP_FPS, 10)
        
    cv2.namedWindow('Template Matching')

    # Arduinoのシリアルポートを開く
    ser = serial.Serial('/dev/cu.usbmodem2201', 9600)
    time.sleep(2) # Arduinoがリセットされるのを待つ

    # クロップするサイズを設定
    crop_width = 800
    crop_height = 1000

    while True:
        # Webカメラからフレームを取得
        ret, frame = cap.read()
        if not ret:
            break
    
        # 中央の領域を切り取る
        height, width, _ = frame.shape
        x = (width - crop_width) // 2
        y = (height - crop_height) // 2
        cropped_frame = frame[y:y+crop_height, x:x+crop_width]
    
        # テンプレートマッチングを実行
        result = cv2.matchTemplate(cropped_frame, template, cv2.TM_CCOEFF_NORMED)
        min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(result)
    
        # マッチングの結果から枠を描画
        h, w, _ = template.shape
        top_left = max_loc
        bottom_right = (top_left[0] + w, top_left[1] + h)
        cv2.rectangle(cropped_frame, top_left, bottom_right, (0, 0, 255), 2)

        # 枠の中心位置からサーボの角度を計算
        center_y = crop_height - top_left[1] + h // 2
        degree = posToDegree(center_y)
        print("center_y: " + str(center_y) + ", degree: " + str(degree))

        # サーボの角度をArduinoに送信
        data = str(degree) + "," + str(degree)
        ser.write(str(data).encode())
    
        # 結果をウィンドウに表示
        cv2.imshow('Template Matching', cropped_frame)
    
        # 'q' キーが押されたらループを終了
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    
    # カメラとウィンドウをクリーンアップ
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()  
