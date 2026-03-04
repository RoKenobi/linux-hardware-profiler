#!/usr/bin/env python3
import matplotlib.pyplot as plt
import csv
import sys

def plot_latency(filename):
    try:
        timestamps = []
        latencies = []
        
        with open(filename, 'r') as f:
            reader = csv.reader(f)
            for row in reader:
                if len(row) >= 2:
                    timestamps.append(row[0])
                    latencies.append(float(row[1].replace('ns', '')))
        
        plt.figure(figsize=(10, 5))
        plt.plot(latencies, marker='o')
        plt.title('Memory Latency Over Time')
        plt.xlabel('Test Run')
        plt.ylabel('Latency (ns)')
        plt.grid(True)
        plt.savefig('latency_plot.png')
        print("Plot saved as latency_plot.png")
        
    except Exception as e:
        print(f"Error plotting: {e}")

if __name__ == "__main__":
    file = sys.argv[1] if len(sys.argv) > 1 else "../metrics.csv"
    plot_latency(file)
