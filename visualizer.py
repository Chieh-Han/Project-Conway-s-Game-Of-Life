import os
from PIL import Image, ImageDraw, ImageFont

def create_gif(output_folder="output", gif_name="simulation.gif", scale=50):
    files = [f for f in os.listdir(output_folder) if f.endswith('.pbm')]
    files.sort(key=lambda x: int(x.split('_')[1].split('.')[0]))

    if not files: return

    # 1. FIND ABSOLUTE MAX SIZE 
    abs_max_w, abs_max_h = 0, 0
    for f in files:
        with Image.open(os.path.join(output_folder, f)) as img:
            abs_max_w = max(abs_max_w, img.width)
            abs_max_h = max(abs_max_h, img.height)

    sim_size = (abs_max_w * scale, abs_max_h * scale)
    frames = []

    # 2. LOAD FONT
    try:
        font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 60)
    except:
        font = ImageFont.load_default()

    # 3. START FRAME
    start = Image.new("RGB", sim_size, color="white")
    ImageDraw.Draw(start).text((sim_size[0]//2, sim_size[1]//2), "START", fill="green", font=font, anchor="mm")
    frames.append(start)

    # 4. PROCESS
    for i, filename in enumerate(files):
        path = os.path.join(output_folder, filename)
        with Image.open(path) as img:

            canvas = Image.new("RGB", (abs_max_w, abs_max_h), color="white")
            
            canvas.paste(img, (0, 0)) 
            
            img_resized = canvas.resize(sim_size, resample=Image.NEAREST)
            # Add Generation Number
            ImageDraw.Draw(img_resized).text((sim_size[0]-20, sim_size[1]-20), f"Gen: {i}", fill="gray", anchor="rd")
            frames.append(img_resized)

    # 5. END FRAME
    end = Image.new("RGB", sim_size, color="white")
    ImageDraw.Draw(end).text((sim_size[0]//2, sim_size[1]//2), "END", fill="red", font=font, anchor="mm")
    frames.append(end)

    frames[0].save(gif_name, save_all=True, append_images=frames[1:], duration=500, loop=0)
    print(f"Success! {gif_name} created.")

if __name__ == "__main__":
    create_gif()