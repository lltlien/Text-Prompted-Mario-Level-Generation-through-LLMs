import glob
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline

def plot_paths(paths, colors):
    for path, color in zip(paths, colors):
        x_coords, y_coords = path
        
        # Loại bỏ các điểm x trùng lặp trên trục x
        unique_indices = np.unique(x_coords, return_index=True)[1]
        x_coords_unique = np.array(x_coords)[unique_indices]
        y_coords_unique = np.array(y_coords)[unique_indices]

        # Tạo đường cong mượt mà
        x_smooth = np.linspace(min(x_coords_unique), max(x_coords_unique), 300)
        y_smooth = make_interp_spline(x_coords_unique, y_coords_unique)(x_smooth)
        
        plt.plot(x_smooth, y_smooth, color, linewidth=1.0)
        
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('250 levels')
    plt.xlim(0, 100)
    plt.ylim(0, 14)
    plt.grid(True)
    plt.gca().set_aspect('equal')
    plt.show()
    plt.savefig('output.png')  # Lưu ảnh cuối cùng với tên là 'output.png'


def extract_path(level, height):
    points = []

    for y, row in enumerate(level):
        for x, char in enumerate(row):
            if char == 'x':
                points.append((x, height - y))

    points.sort(key=lambda p: (p[0], p[1]))

    x_coords = [p[0] for p in points]
    y_coords = [p[1] for p in points]

    return x_coords, y_coords

# Đường dẫn đến thư mục chứa các levels
levels_folder = './250'

# Định dạng tệp của levels
levels_format = '*.txt'

# Danh sách các màu sắc cho các level
cmap = plt.get_cmap('gnuplot')
colors = [cmap(i) for i in np.linspace(0, 1, 250)] # Thêm các màu sắc khác tùy ý

# Lấy danh sách tệp levels trong thư mục
level_files = glob.glob(levels_folder + '/' + levels_format)

paths = []

# Trích xuất đường đi từ mỗi level và thêm vào danh sách paths
for file in level_files:
    with open(file, 'r') as f:
        level = f.read().splitlines()
        x_coords, y_coords = extract_path(level, 14)
        paths.append((x_coords, y_coords))

# Vẽ các đường đi mượt hơn với màu sắc tương ứng
plt.figure(figsize=(80, 4))
plot_paths(paths, colors)