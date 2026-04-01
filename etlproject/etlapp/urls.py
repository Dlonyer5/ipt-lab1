from django.urls import path
from .views import upload_and_run

urlpatterns = [
    path("etl/", upload_and_run),
]