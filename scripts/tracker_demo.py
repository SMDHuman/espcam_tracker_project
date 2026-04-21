import time
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from modules.tracker_interface import Tracker_Interface

# --------------------------------------------------------------------------
# Example usage with matplotlib
# --------------------------------------------------------------------------
if(__name__ == "__main__"):
  # Example usage
  tracker = Tracker_Interface("/dev/ttyUSB0")
  print("Tracker interface initialized")
  time.sleep(1)
  #...
  peer_list = tracker.get_peer_list()
  print("peer list: ", peer_list)
  #...
  plt.ion()  # Enable interactive mode
  fig, ax = plt.subplots()
  ax.set_xlim(0, 240)  # ESP32-CAM typical resolution
  ax.set_ylim(176, 0)  # Inverted Y-axis for image coordinates
  #...
  last_fcount_time = time.time()
  last_fcount = 0
  try:
    while plt.fignum_exists(fig.number):  # Check if figure window exists
      #print("-"*80)
      peer_count = tracker.get_peer_count()
      print("peer count: ", peer_count)
      print("peer list: ", tracker.get_peer_list())
      print("total frame: ", tracker.get_frame_count())
      fcount = tracker.get_frame_count()
      #...
      ax.clear()
      ax.set_xlim(0, 240)
      ax.set_ylim(176, 0)
      labeled_peers = set()
      #...
      fcount = tracker.get_frame_count()
      now = time.time()
      current_fps = round((fcount-last_fcount)/(now-last_fcount_time))
      print("fps: ", current_fps)
      ax.set_title(f'FPS: {current_fps}')
      last_fcount_time = now
      #...
      for i in range(peer_count+1):
        # print(f" |-----------------")
        # print(f" | peer #{i} ")
        # print("  +-total frames: ", tracker.get_frame_count(i))
        points = tracker.get_points(i)
        # print("  +-points: ", points)
        # print(f"id{i} trk_erode:", tracker.get_config("trk_erode", i))
        # Draw rectangles for each point
        for rect in points:
          x1, y1, x2, y2 = rect
          width = x2 - x1
          height = y2 - y1
          # Only add label if this peer hasn't been labeled yet
          label = f'Peer {i}' if i not in labeled_peers else ""
          ax.add_patch(Rectangle((x1, y1), width, height, 
                fill=False, color=f'C{i}', 
                label=label))
          labeled_peers.add(i)
        ax.legend()
      #...
      plt.draw()
      plt.pause(0.1)
      last_fcount = fcount
  except KeyboardInterrupt:
    plt.close(fig)
