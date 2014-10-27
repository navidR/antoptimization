// Defined Variable for program
#define ZERO 0
#define GRAPH_WIN_CONTAINER_BORDER_WIDTH 5
#define GRAPH_WIN_WIDTH 1000
#define GRAPH_WIN_HEIGHT 600
#define DRAWING_AREA_WIDTH 800
#define DRAWING_AREA_HEIGHT 600
#define MAIN_WIN_WIDTH 400
#define MAIN_WIN_HEIGHT 600
#define RESIZABLE FALSE
#define RADIUS 4
#define FIRST_ANGLE 0
#define SECOND_ANGLE 8
#define RGB_SURFACE 1
#define RESERVED_SIZE_OF_ARRAY_POINTS 20
#define DISTANCE 50
#define RED 0.99
#define MODE_INDEX 0
#define SPIN_VERTEX_INDEX 1
#define SPIN_EDGE_INDEX 2
#define MIN_NUMOFANTS 2
#define MAX_NUMOFANTS 500
#define MIN_NUMOFVERTICES 3
#define MAX_NUMOFVERTICES 500
#define DEFAULT_NUMOFEDGES 3
#define MIN_EVAPORATION_RATE 1
#define MAX_EVAPORATION_RATE 100
#define INCREMENT_RATE 1

// used EVENT
const char *EVENT_DESTROY = "destroy";
const char *EVENT_CONFIGURE_EVENT = "configure-event";
const char *EVENT_MOTION_NOTIFY_EVENT = "motion-notify-event";
const char *EVENT_CLICKED = "clicked";
const char *EVENT_DRAW = "draw";
const char *EVENT_DELETE_EVENT = "delete-event";
const char *EVENT_TOGGLED = "toggled";
const char *EVENT_BUTTON_PRESS_EVENT = "button-press-event";
const char *EVENT_VALUE_CHANGED = "value-changed";

// global strings
const char *mainwin_ui_name = "mainwindow.glade";
const char *mainwin_title = "Main Window";
const char *graphwin_title = "Graph Window";


// global string , for loading ui file objects
const char *mainwin_ui_frame_name = "frame_ui";
const char *input_evaporation_rate_name = "input_evaporation_rate";
const char *input_numofants_name = "input_numofants";
const char *input_numofvertices_name = "input_numofvertices";
const char *input_numofedges_name = "input_numofedges";
const char *button_drawing_mode_name = "button_drawing_mode";
const char *button_solve_problem_name = "button_solve_problem";
const char *button_generating_random_graph_name = "button_generating_random_graph";

// global variable
static cairo_surface_t *surface = NULL;

typedef enum { DRAWING_MODE, RANDOM_MODE } _mode;

// structure for saving clicked points lcoation in drawing area
struct _points{
	gint x;
	gint y;
};

// bag for keeping two item of _points
struct _bag{
	struct _points* first_item;
	struct _points* second_item;
} bag;

// array of _points for tracking points
static GArray *ui_points;

