#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <AL/alut.h>

int
do_body(int argc, char **argv)
{
    ALuint m_beep_buffer;
    ALuint m_beep_source;

    //m_beep_buffer = alutCreateBufferFromFile("helloworld.wav");
    m_beep_buffer = alutCreateBufferWaveform(
        ALUT_WAVEFORM_SINE,
        2400,
        0,
        0.5);

    alGenSources(1, &m_beep_source);
    alSourcei(m_beep_source, AL_BUFFER, m_beep_buffer);

    alSourceStop(m_beep_source);
    alSourcei(m_beep_source, AL_LOOPING, AL_FALSE);
    alSourcePlay(m_beep_source);

    alutSleep(1);

    alDeleteBuffers(1, &m_beep_buffer);
    alDeleteSources(1, &m_beep_source);

    return EXIT_SUCCESS;
}

int
main(int argc, char **argv)
{
    /* Initialise ALUT and eat any ALUT-specific commandline flags. */
    if(!alutInit(&argc, argv))
    {
        ALenum error = alutGetError();
        fprintf(stderr, "%s\n", alutGetErrorString(error));
        return EXIT_FAILURE;
    }

    int ret = do_body(argc, argv);

    alutExit();
    return ret;
}
