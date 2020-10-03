# PPM_viewer
A portable pixmap format image editor and displayer written in C++

Enter the src directory

start xming server

```
make
./glut_main
```

- case 'q':
- case 27: // escape character means to quit the program \
    exit(0); \
    break;
- case 'z':
    g_app_data->zoomIn(); \
    break;
- case 'Z':
    g_app_data->zoomOut(); \
    break;
- case 'j':
    g_app_data->julia(); \
    break;
- case 'm':
    g_app_data->mandelbrot(); \
    break;
- case 'J':
    g_app_data->setMode(g_app_data->MODE_JULIA_PARAMETERS); \
    break;
- case 'w':
    g_app_data->writePPMFile(); \
    break;
- case 'a':
    g_app_data->toggleAntiAlias(); \
    break;
- case '0':
    g_app_data->setColorTable(0); \
    break;
- case '1':
    g_app_data->setColorTable(1); \
    break;
- case '2':
    g_app_data->setColorTable(2); \
    break;
- case '3':
    g_app_data->setColorTable(3); \
    break;
- case 'j': \
    g_app_data->julia(); \
    break;
- case 'm': \
    g_app_data->mandelbrot(); \
    break;
- case 'J': \
    g_app_data->setMode(g_app_data->MODE_JULIA_PARAMETERS); \
    break;
- case 'w': \
    g_app_data->writePPMFile(); \
    break;
- case 'a': \
    g_app_data->toggleAntiAlias(); \
    break;
- case '0': \
    g_app_data->setColorTable(0); \
    break;
- case '1': \
    g_app_data->setColorTable(1); \
    break;
- case '2': \
    g_app_data->setColorTable(2); \
    break;
- case '3': \
    g_app_data->setColorTable(3); \
