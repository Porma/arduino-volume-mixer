# noinspection PyShadowingBuiltins

class Channel:
    def __init__(self, id):
        self.id = str(id)
        self.program = None
        print("Channel " + self.id + " created")

    def assign_program(self, session):
        self.program = session
        print(f"{self.program.Process.name()} assigned to channel {self.id}")

    def unassign_program(self):
        print(f"{self.program.Process.name()} unassigned from channel {self.id}")
        self.program = None

