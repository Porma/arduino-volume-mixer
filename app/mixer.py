import win32process
import win32gui
import psutil
from pycaw.pycaw import AudioUtilities

from channel import Channel


class Mixer:
    channels = []
    enc_range = range(0, 2) # encoders to use - can be range or array

    def __init__(self):
        for i in self.enc_range:  # config value
            self.channels.append(Channel(i))
        print("Mixer created")

    def process_input(self, cmd):
        channel = int(cmd[0])
        action = int(cmd[1])

        if action == 0:
            print("Encoder " + str(channel) + ": volume down")
        elif action == 1:
            print("Encoder " + str(channel) + ": volume up")
        elif action == 2:
            print("Encoder " + str(channel) + ": button down")
        elif action == 3:
            # print("Encoder " + str(channel) + ": button up")
            # self.channels[channel].button_up()
            self.__button_up(channel)

    def __button_up(self, channel):
        # logic to figure out assign or unassign
        # self.assign_program(channel)

        active = self.__get_active_session()

        # End fn if no active session found
        if not active:
            return

        # Unassign program from other channels if assigned
        for ch in self.channels:
            if ch.program and ch.program.Process.name() == active.Process.name():
                ch.unassign_program()
                break

        # Pass session to channel
        self.channels[channel].assign_program(active)

        # DEBUG
        # for ch in self.channels:
        #     # print(ch.id + " - " + ch.program)
        #     # print(ch.id)
        #     # print(ch.program.Process.name())
        #     # print("")
        #     print(ch.id)
        #
        #     if ch.program:
        #         print(ch.program.Process.name())
        #     else:
        #         print("no session")
        #
        #     print("")

    def __get_active_session(self):
        sessions = AudioUtilities.GetAllSessions

        active_window = win32gui.GetForegroundWindow()
        active_pid = win32process.GetWindowThreadProcessId(active_window)[1]
        active_process = psutil.Process(active_pid).name()

        session = next(
            (s for s in sessions() if s.Process and s.Process.name() == active_process), None)

        # print(active_window)
        # print(active_pid)
        # print(active_process)
        # print(session)
        # print(session.Process.name())

        return session

