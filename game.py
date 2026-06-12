# Setup for game characters
class Character:
    def __init__(self, name, hi_msg, chat_tree):
        self.name = name
        self.hi_msg = hi_msg
        self.chat_tree = chat_tree

    def talk(self):
        print("\n" + self.name + " says: " + self.hi_msg)
        lines = list(self.chat_tree.keys())
        while True:
            print("\nOptions:")
            for idx, line in enumerate(lines, start=1):
                print(str(idx) + ". " + line)
            print(str(len(lines) + 1) + ". Goodbye")
            
            pick = input(">> ").strip()
            if pick.isdigit():
                num = int(pick)
                if num == len(lines) + 1:
                    break
                elif 1 <= num <= len(lines):
                    text = lines[num-1]
                    print("\nYou: " + text)
                    print(self.name + ": " + self.chat_tree[text])
                    continue 
            print("Try again.")

# Game world setup
world = {
    "cell": "Rusted iron bars and wet stone walls.",
    "hallway": "Dark stone corridor with some torches.",
    "weapon room": "Old racks holding dusty, broken swords.",
    "graves": "Chilly room filled with old stone tombs.",
    "barracks": "Messy table with cards and food scraps.",
    "throne room": "A big hall with a giant stone chair."
}

paths = {
    "cell": {"out": "hallway"},
    "hallway": {"in": "cell", "north": "barracks", "east": "weapon room", "down": "graves"},
    "weapon room": {"west": "hallway"},
    "graves": {"up": "hallway"},
    "barracks": {"south": "hallway", "north": "throne room"},
    "throne room": {"south": "barracks"}
}

# Put characters in rooms
spawns = {
    "weapon room": Character("Ghostly Smith", "I forge forever...", {
        "Ask about weapons": "They are all rusted. You need the big boss key.",
        "How did you die?": "Blade explosion."
    }),
    "barracks": Character("Goblin", "Don't hit me!", {
        "Where is the exit?": "Go north past the throne room.",
        "Buy map": "Need shiny gems for that."
    })
}

# Start the game loop
here = "cell"
print("=== DUNGEON CRAWLER ===")

while True:
    print("\nYou are in: " + here.upper())
    print("Look: " + world[here])
    
    guy = spawns.get(here)
    if guy:
        print("Someone is here: " + guy.name)
        
    cmd = input("What to do? (move/talk/q): ").strip().lower()
    
    if cmd == "move":
        ways = list(paths.get(here, {}).keys())
        if not ways:
            print("Trapped.")
            continue
            
        print("Exits: " + ", ".join(ways))
        go = input("Direction: ").strip().lower()
        if go in paths[here]:
            here = paths[here][go]
        else:
            print("Can't go there.")
            
    elif cmd == "talk":
        if guy:
            guy.talk()
        else:
            print("Nobody is here.")
            
    elif cmd == "q":
        print("Bye!")
        break
    else:
        print("Unknown command.")