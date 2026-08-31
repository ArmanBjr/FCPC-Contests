import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans, MeanShift, DBSCAN, AgglomerativeClustering

# تولید خوشه‌های کروی
centers = [[1, 1], [-1, -1], [1, -1]]
X, _ = make_blobs(n_samples=100, centers=centers, cluster_std=0.2, random_state=42)

# اضافه کردن نویز تصادفی (داده‌های پرت)
noise = np.random.uniform(low=-3, high=3, size=(50, 2))
X = np.vstack([X, noise])

# تعریف الگوریتم‌ها
algorithms = {
    "K-Means": KMeans(n_clusters=3, n_init=10),
    "MeanShift": MeanShift(),
    "DBSCAN": DBSCAN(eps=0.4, min_samples=5),
    "Agglomerative": AgglomerativeClustering(n_clusters=3)
}

# رسم نتایج
plt.figure(figsize=(15, 4))
for i, (name, algo) in enumerate(algorithms.items()):
    labels = algo.fit_predict(X)
    plt.subplot(1, 4, i+1)
    plt.scatter(X[:, 0], X[:, 1], c=labels, cmap='viridis', s=20)
    plt.title(name)
plt.show()